/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:09:18 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/26 10:57:14 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	grep_check(t_data *data, char **argv)
{
	if (data->infile == -1 || data->outfile == -1)
	{
		if (ft_strcmp(data->cmd1, "/usr/bin/grep") == 0)
		data->cmd1 = argv[2];
		if (ft_strcmp(data->cmd2, "/usr/bin/grep") == 0)
		data->cmd2 = argv[3];
	}
}

void	no_path_check(t_data *data, char **argv)
{
	if (access(argv[2], X_OK) == -1 && access(argv[3], X_OK) == -1)
	{
		if (data->infile == -1)
			error_msg(argv[2], 0, 0);
		else
			error_msg(argv[2], 0, 1);
		error_msg(argv[3], 0, 1);
		exit(127);
	}
	else if (access(argv[2], X_OK) == -1 && access(argv[3], X_OK) == 0)
	{
		data->args2 = check_cmd(argv[3]);
		data->cmd2 = check_path_array(data, data->args2[0]);
		error_msg(argv[2], 0, 0);
	}
	else if (access(argv[2], X_OK) == -1)
		error_msg(argv[2], 0, 0);
	else if (access(argv[3], X_OK) == -1)
	{
		error_msg(argv[3], 0, 0);
		exit (127);
	}
}

void	input_check(t_data *data, char **argv, char **envp)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		error_msg(argv[1], 0, 1);
	data->outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (data->outfile == -1)
		error_msg(argv[4], 2, 0);
	initialize(data, argv, envp);
	grep_check (data, argv);
	if (access(data->cmd1, X_OK) == -1 && access(data->cmd2, X_OK) == -1)
	{
		if (data->infile != -1)
			error_msg(data->cmd1, 1, 1);
		error_msg(data->cmd2, 1, 1);
		exit(127);
	}
	if (access(data->cmd1, X_OK) == -1 && access(data->cmd2, X_OK) == 0)
	{
		if (data->infile != -1)
			error_msg(data->cmd1, 1, 1);
	}
	else if (access(data->cmd1, X_OK) == -1)
		error_msg(data->cmd1, 1, 0);
	else if (access(data->cmd2, X_OK) == -1)
		error_msg(data->cmd2, 1, 0);
	data->status = 0;
}

void	error_msg(char *msg, int i, int j)
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
	else if (i == 2)
	{
		ft_putstr_fd("Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	if (j == 0)
		exit (status);
}
