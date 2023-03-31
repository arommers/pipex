/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 11:13:24 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/31 13:50:09 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h> // for malloc and free
# include <stdio.h> // for perro
# include <sys/types.h> // for pid_t type
# include <sys/wait.h> // for waitpi
# include <fcntl.h> // for open
# include <unistd.h> // for pipe, fork, execve, dup2, and close

typedef struct s_data {
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;
}	t_data;


#endif