/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:09:18 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/22 16:11:57 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_check(t_data *data, char **argv, char **envp)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
	data->outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (data->outfile == -1)
		error_msg(argv[4], 0);
	data->path = get_path(envp);
	data->paths = ft_split(data->path, ':');
	data->args1 = check_cmd(argv[2]);
	data->args2 = check_cmd(argv[3]);
	data->cmd1 = check_path_array(data, data->args1[0]);
	data->cmd2 = check_path_array(data, data->args2[0]);
	if (access(data->cmd1, X_OK) == -1 && access(data->cmd2, X_OK) == -1)
	{
		ft_printf("pipex: %s: command not found\n", data->cmd1);
		ft_printf("pipex: %s: command not found\n", data->cmd2);
		exit(127);
	}
	if (access(data->cmd1, X_OK) == -1 && access(data->cmd2, X_OK) == 0)
		ft_printf("pipex: %s: command not found\n", data->cmd1);
	else if (access(data->cmd1, X_OK) == -1)
		error_msg(data->cmd1, 1);
	else if (access(data->cmd2, X_OK) == -1)
		error_msg(data->cmd2, 1);
	data->status = 0;
}


int	check_infile(char **argv)
{
	if (access (argv[1], X_OK) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	else
		return (0);
}

void	unset_error(t_data *data, char **argv, int i)
{
	if (check_infile(argv))
	{
		data->paths = ft_split(argv[3], ' ');
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(data->paths[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		ft_free(data->paths);
	}
	else
	{
		while (i <= 3)
		{
			data->paths = ft_split(argv[i++], ' ');
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(data->paths[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("No such file or directory", 2);
			ft_putstr_fd("\n", 2);
			ft_free(data->paths);
		}
	}
	exit (127);
}

void	error_msg(char *msg, int i)
{
	int	status;

	status = 1;
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	if (i == 1)
	{
		ft_putstr_fd("command not found", 2);
		ft_putstr_fd("\n", 2);
		status = 127;
	}
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	exit (status);
}
