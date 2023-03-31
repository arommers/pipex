/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 14:02:07 by arommers      #+#    #+#                 */
/*   Updated: 2023/03/31 16:41:23 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "libft.h"


char	*get_path(char **envp);
char	*find_path(char **path_split, char **cmd);

void	leaks(void)
{
	system("leaks a.out");
}
char	*get_path(char **envp)
{
	while (*envp)
	{
		if ((ft_strncmp(*envp, "PATH=", 5)) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*make_path(char **paths, char **cmd)
{
	char	*tmp;
	char	*tmp_cmd;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		tmp_cmd = ft_strjoin(tmp, *cmd);
		if (access(tmp_cmd, F_OK) == 0)
			return (tmp_cmd);
		free(tmp_cmd);
		paths++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
	char	*pathstr;
	char	**path_split;

	atexit(leaks);
	if (argc != 3)
		return (1);
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		exit(1);
	pathstr = get_path(envp);
	path_split = ft_split(pathstr, ':');
	// int j = 0;
	// while (cmd[j])
	// {
	// 	printf("arguments: %s\n", cmd[j]);
	// 	j++;
	// }
	// j = 0;
	// while (path_split[j])
	// {
	// 	printf("found path: %s\n", path_split[j]);
	// 	j++;
	// }
	pathstr = make_path(path_split, cmd);
	printf("%s\n", pathstr);
	return (0);
}
