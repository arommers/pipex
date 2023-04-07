/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 11:09:22 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/07 13:44:38 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_leaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (argc != 5)
		error_msg("Is it so hard to give me 5 arguments? :");
	initialize(data, argv, envp);
	data->child1 = fork();
	if (data->child1 == -1)
		error_msg("ERROR making babies:");
	if (data->child1 == 0)
		child_process_one(data, argv, envp);
	data->child2 = fork();
	if (data->child2 == -1)
		error_msg("ERROR making babies:");
	if (data->child2 == 0)
		child_process_two(data, argv, envp);
	close (data->buffer[0]);
	close (data->buffer[1]);
	waitpid(data->child1, &data->status, 0);
	waitpid(data->child2, &data->status, 0);
	ft_free(data->paths);
	free(data);
	atexit(check_leaks);
	return (0);
}
