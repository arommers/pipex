/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 11:09:22 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/17 14:07:10 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (argc != 5)
		error_msg("Invalid number of arguments\n", 1);
	initialize(data, envp);
	data->child1 = fork();
	if (data->child1 == -1)
		error_msg("ERROR making babies:", 0);
	if (data->child1 == 0)
		child_process_one(data, argv, envp);
	data->child2 = fork();
	if (data->child2 == -1)
		error_msg("ERROR making babies:", 0);
	if (data->child2 == 0)
		child_process_two(data, argv, envp);
	close (data->buffer[0]);
	close (data->buffer[1]);
	waitpid(data->child1, NULL, 0);
	waitpid(data->child2, &data->status, 0);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->status = 128 + WTERMSIG(data->status);
	else
		data->status = 1;
	exit (data->status);
}
