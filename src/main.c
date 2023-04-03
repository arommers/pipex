/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 11:09:22 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/03 13:06:21 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5)
		return (1);
	intialize(data, argv, envp);
	if (data->child1 == -1)
	{
		perror("ERROR making babies");
		exit(EXIT_FAILURE);
	}
	if (data->child1 == 0)
		run_child1(data, argcv, envp);
	data->child2 = fork();
	if (data->child2 == -1)
	{
		perror("ERROR making babies");
		exit(EXIT_FAILURE);
	}
	if (data->child2 == 0)
		run_child2(data, argv, envp);
}
