/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:09:18 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/17 13:59:18 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_msg(char *msg, int i)
{
    int status;

    status = 1;
    ft_putstr_fd("pipex: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd(": ", 2);
    if (i == 1)
    {
        ft_putstr_fd("command not found", 2);
        ft_putstr_fd("\n", 2);
    }
    else
    {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
    }
    if (errno == EACCES)
        status = 126;
    else if (errno == ENOENT || errno == ENOTDIR)
        status = 127;
    else if (errno == ENOEXEC)
        status = 126;
    else if (errno == EINTR)
        status = 130;
    exit (status);
}

// void    error_msg(char *msg)
// {
//     int status;

//     status = 1;
//     if (errno == EACCES)
//         status = 126;
//     else if (errno == ENOENT || errno == ENOTDIR)
//         status = 127;
//     else if (errno == ENOEXEC)
//         status = 126;
//     else if (errno == EINTR)
//         status = 130;
//     write(STDERR_FILENO, msg, ft_strlen(msg));
//     write(STDERR_FILENO, "\n", 1);
//     exit (status);
// }

// void	error_msg(char *msg)
// {
// 	perror(msg);
// 	exit(errno);
// }
