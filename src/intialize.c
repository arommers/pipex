/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intialize.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 10:32:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/03 17:11:56 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		i++;
	}
	return (NULL);
}

char	*check_path_array(t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp_array;

	i = 0;
	if (!data->paths || !*data->paths)
	{
		if (access(data->args[0], X_OK) == 0)
			return (ft_strdup(data->args[0]));
	}
	while (data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		if (access(tmp_array, X_OK) == 0)
		{
			free (tmp);
			return (tmp_array);
		}
		free (tmp);
		free (tmp_array);
		i++;
	}
	return (NULL);
}

void	*intialize(t_data *data, char **argv, char **envp)
{
	data->status = 0;
	data->infile = open(argv[1], RDONLY);
	data->outfile = open(argv[5], O_CREATE | O_TRUNC | O_RDWR, 0666);
	if (data->infile == -1 || data->outfile == -1)
		error_msg("ERROR opening files:");
	data->path = get_path(envp);
	data->paths = ft_split(path, ' ');
	if (pipe (data->buffer) == -1)
		error_msg("ERROR creating pipe:");
}
