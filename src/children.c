/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 14:45:39 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/03 17:15:37 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_child(t_data *data, char **argv, char **envp)
{
	close (data->buffer[0]);
	dup2 (data->infile, STDIN_FILENO);
	dup2 (data->buffer[1], STDOUT_FILENO);
	data->args = ft_split (argv[2], ' ');
	if (data->args == NULL)
		error_msg("ERROR arguments not valid:");
	data->cmd = check_path_array(data);
	execve(data->cmd, data->args[0], envp);
	close (data->buffer[1]);
}
