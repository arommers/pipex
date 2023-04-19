/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:09:18 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/19 16:42:19 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	unset_error(char **argv, int i)
{
	int	status;

	status = 1;
	if (access (argv[1], X_OK) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		while (i < 4)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(argv[i++], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("command not found", 2);
			ft_putstr_fd("\n", 2);
		}
		status = 127;
	}
	exit (status);
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
