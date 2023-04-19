/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:09:18 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/19 21:37:08 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		return(0);
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
		if (errno == EACCES || errno == ENOEXEC)
			status = 126;
	}
	if (errno == ENOENT || errno == ENOTDIR)
		status = 127;
	exit (status);
}
