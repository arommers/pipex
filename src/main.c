/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 11:09:22 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/28 14:29:42 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	leaks()
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	atexit(leaks);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(1);
	if (argc != 5)
		error_msg("Invalid nbr of arguments\n", 0, 0);
	input_check(data, argv, envp);
	if (pipe (data->buffer) == -1)
		error_msg("ERROR creating pipe:", 0, 0);
	data->child1 = fork();
	if (data->child1 == -1)
		error_msg("fork", 0, 0);
	if (data->child1 == 0)
		child_process_one(data, envp);
	data->child2 = fork();
	if (data->child2 == -1)
		error_msg("fork", 0, 0);
	if (data->child2 == 0)
		child_process_two(data, envp);
	de_initialize(data);
	exit (data->status);
}
