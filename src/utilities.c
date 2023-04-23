/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 10:32:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/23 13:38:50 by arommers      ########   odam.nl         */
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

char	*check_alt_path(char *arg)
{
	if (access(arg, X_OK) == 0)
		return (arg);
	return (NULL);
}

char	*check_path_array(t_data *data, char *args)
{
	int		i;
	char	*tmp;
	char	*tmp_array;
	char	*cmd_arg;

	i = 0;
	cmd_arg = args;
	if (check_alt_path(cmd_arg) != NULL)
		return (cmd_arg);
	while (data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i++], "/");
		tmp_array = ft_strjoin(tmp, cmd_arg);
		if (access(tmp_array, X_OK) == 0)
		{
			free (tmp);
			return (tmp_array);
		}
		free (tmp);
		free (tmp_array);
	}
	return (cmd_arg);
}

void	initialize(t_data *data, char **argv, char **envp)
{
	data->status = 0;
	data->path = get_path(envp);
	if (data->path == NULL)
	{
		if (access(argv[2], X_OK) == -1 && access(argv[3], X_OK) == -1)
		{
			ft_printf("pipex: %s: No such file or directory\n", argv[2]);
			ft_printf("pipex: %s: No such file or directory\n", argv[3]);
			exit(127);
		}
		else if (access(argv[2], X_OK) == -1)
		{
			ft_printf("pipex: %s: No such file or directory\n", argv[2]);
			exit (0);
		}
		else if (access(argv[2], X_OK) == -1)
		{
			ft_printf("pipex: %s: No such file or directory\n", argv[2]);
			exit (127);
		}
		// unset_error(data, argv, 2);
	}
	else
		data->paths = ft_split(data->path, ':');
	data->args1 = check_cmd(argv[2]);
	data->args2 = check_cmd(argv[3]);
	data->cmd1 = check_path_array(data, data->args1[0]);
	data->cmd2 = check_path_array(data, data->args2[0]);
}

void	de_initialize(t_data *data)
{
	close (data->buffer[0]);
	close (data->buffer[1]);
	waitpid(data->child1, NULL, 0);
	waitpid(data->child2, &data->status, 0);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else
		data->status = 1;
}
