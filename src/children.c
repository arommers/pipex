/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 14:45:39 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/10 17:47:26 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_one(t_data *data, char **argv, char **envp)
{
	close (data->buffer[0]);
	dup2 (data->infile, STDIN_FILENO);
	dup2 (data->buffer[1], STDOUT_FILENO);
	close (data->buffer[1]);
	data->args = neo_split (argv[2], ' ');
	if (data->args == NULL)
		error_msg("ERROR arguments not valid:");
	data->cmd = check_path_array(data);
	execve(data->cmd, data->args, envp);
}

void	child_process_two(t_data *data, char **argv, char **envp)
{
	close (data->buffer[1]);
	dup2 (data->outfile, STDOUT_FILENO);
	dup2 (data->buffer[0], STDIN_FILENO);
	close (data->buffer[0]);
	data->args = neo_split (argv[3], ' ');
	if (data->args == NULL)
		error_msg("ERROR arguments not valid:");
	data->cmd = check_path_array(data);
	execve(data->cmd, data->args, envp);
}
