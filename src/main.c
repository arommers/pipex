/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 11:09:22 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/19 14:53:30 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (argc != 5)
		error_msg("Invalid nbr of arguments\n", 1);
	initialize(data, argv, envp);
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
	de_initialize(data);
	exit (data->status);
}
