/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 11:13:24 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/03 13:08:54 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h> // for malloc and free
# include <stdio.h> // for perro
# include <errno.h> // for errno
# include <sys/types.h> // for pid_t type
# include <sys/wait.h> // for waitpid
# include <fcntl.h> // for open
# include <unistd.h> // for pipe, fork, execve, dup2, and close

typedef struct s_data {
	pid_t	child1;
	pid_t	child2;
	int		infile;
	int		outfile;
	int		buffer[2];
	char	*path;
	char	**paths;
	char	**args;
}	t_data;

void	intialize(t_data data, char **argv, char **envp);

#endif