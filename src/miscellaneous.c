/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:09:18 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/14 14:57:33 by arommers      ########   odam.nl         */
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

void	error_msg(char *msg)
{
	perror(msg);
	exit(errno);
}
