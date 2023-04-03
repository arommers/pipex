/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intialize.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 10:32:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/03 13:00:14 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*intialize(t_data *data, char **argv, char **envp)
{
	data->infile = open(argv[1], RDONLY);
	data->outfile = open(argv[5], O_CREATE | O_TRUNC | O_RDWR, 0666);
	if (data->infile || data->outfile == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	data->path = get_path(envp);
	if (data->path == NULL)
	{
		perror("NO VALID PATH");
		exit(EXIT_FAILURE);
	}
	data->paths = ft_split(path, ' ');
	if (data->paths == NULL)
	{
		perror("NO VALID PATH");
		exit(EXIT_FAILURE);
	}
	if (data->pipe(buffer) == -1)
	{
		perror("ERROR creating pipe");
		exit(EXIT_FAILURE);
	}
}
