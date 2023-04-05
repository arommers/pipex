/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 10:32:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/05 12:56:04 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp)
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

char	*check_alt_path(t_data *data)
{
	if (access(data->args[0], X_OK) == 0)
		return (ft_strdup(data->args[0]));
	else if (ft_strchr(data->args[0], '/') != NULL
		&& access(data->args[0], X_OK) == 0)
		return (ft_strdup(data->args[0]));
	return (NULL);
}

char	*check_path_array(t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp_array;

	i = 0;
	if (!data->paths || !*data->paths)
		return (check_alt_path(data));
	while (data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		tmp_array = ft_strjoin(tmp, data->args[0]);
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

void	intialize(t_data *data, char **argv, char **envp)
{
	data->status = 0;
	data->infile = open(argv[1], O_RDONLY);
	data->outfile = open(argv[5], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (data->infile == -1 || data->outfile == -1)
		error_msg("ERROR opening files:");
	data->path = get_path(envp);
	data->paths = ft_split(data->path, ' ');
	if (pipe (data->buffer) == -1)
		error_msg("ERROR creating pipe:");
}
