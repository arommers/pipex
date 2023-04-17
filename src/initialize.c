/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 10:32:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/17 13:53:14 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*check_alt_path(t_data *data)
{
	if (access(data->args[0], X_OK) == 0)
		return (ft_strdup(data->args[0]));
	return (NULL);
}

char	*check_path_array(t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp_array;

	i = 0;
	if (check_alt_path(data) != NULL)
		return (data->args[0]);
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
	error_msg(data->args[0], 1);
	return (NULL);
}

void	initialize(t_data *data, char **envp)
{
	data->status = 0;
	data->path = get_path(envp);
	if (data->path == NULL)
		exit (0);
	data->paths = ft_split(data->path, ':');
	if (pipe (data->buffer) == -1)
		error_msg("ERROR creating pipe:", 0);
}
