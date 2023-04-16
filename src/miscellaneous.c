/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:09:18 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/16 11:58:52 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	error_msg(char *msg)
// {
// 	char	*error_str;

// 	error_str = strerror(errno);
// 	ft_printf("%s: %s\n", msg, error_str);
// 	exit(EXIT_FAILURE);
// }

int error_msg(char *msg)
{
    int status = 1;
    if (errno == EACCES)
        status = 126;
    else if (errno == ENOENT || errno == ENOTDIR)
        status = 127;
    else if (errno == ENOEXEC)
        status = 126;
    else if (errno == EINTR)
        status = 130;
    write(STDERR_FILENO, msg, ft_strlen(msg));
    write(STDERR_FILENO, "\n", 1);
    exit(status);
}
