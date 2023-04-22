/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 11:13:24 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/22 14:50:26 by arommers      ########   odam.nl         */
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
	int		status;
	int		infile;
	int		outfile;
	int		buffer[2];
	char	*path;
	char	**paths;
	char	*cmd1;
	char	*cmd2;
	char	**args1;
	char	**args2;
}	t_data;

int		neo_strlen(const char *str, char c);
char	**check_cmd(char *argv);
char	**split_quotes(char **tmp, char *cmd);

void	input_check(t_data *data, char **argv, char **envp);
void	error_msg(char *str, int i);
void	unset_error(t_data *data, char **argv, int i);
int		check_infile(char **argv);
char	*get_path(char **envp);
char	*check_alt_path(char *arg);
char	*check_path_array(t_data *data, char *args);
void	initialize(t_data *data, char **argv, char **envp);
void	de_initialize(t_data *data);
void	child_process_one(t_data *data, char **envp);
void	child_process_two(t_data *data, char **envp);

#endif