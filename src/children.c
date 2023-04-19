/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 14:45:39 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/19 14:46:06 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_one(t_data *data, char **argv, char **envp)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		error_msg(argv[1], 0);
	close (data->buffer[0]);
	dup2 (data->infile, STDIN_FILENO);
	dup2 (data->buffer[1], STDOUT_FILENO);
	close (data->buffer[1]);
	data->args = check_cmd(data, argv[2]);
	if (data->args == NULL)
		error_msg("ERROR arguments not valid:", 0);
	data->cmd = check_path_array(data);
	execve(data->cmd, data->args, envp);
}

void	child_process_two(t_data *data, char **argv, char **envp)
{
	data->outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (data->outfile == -1)
		error_msg(argv[3], 0);
	close (data->buffer[1]);
	dup2 (data->outfile, STDOUT_FILENO);
	dup2 (data->buffer[0], STDIN_FILENO);
	close (data->buffer[0]);
	data->args = check_cmd(data, argv[3]);
	if (data->args == NULL)
		error_msg("ERROR arguments not valid:", 0);
	data->cmd = check_path_array(data);
	execve(data->cmd, data->args, envp);
}
