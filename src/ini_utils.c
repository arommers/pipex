/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ini_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 14:31:53 by arommers      #+#    #+#                 */
/*   Updated: 2023/04/03 15:11:05 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	leaks(void)
// {
// 	system("leaks output");
// }

char	*make_path(char **paths, char **cmd)
{
	int		i;
	char	*tmp;
	char	*tmp_cmd;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp_cmd = ft_strjoin(tmp, *cmd);
        printf("Checking path: %s\n", tmp_cmd);
		if (access(tmp_cmd, X_OK) == 0)
		{
            printf("Found valid path: %s\n", tmp_cmd);
			free(tmp);
            return (tmp_cmd);
        }
		free(tmp);
		free(tmp_cmd);
		i++;
	}
    printf("Could not find valid path for command\n");
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
	char	*path;
	char	*pathstr;
	char	**path_split;

	// atexit(leaks);
	if (argc != 3)
		return (1);
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		exit(1);
	pathstr = get_path(envp);
	path_split = ft_split(pathstr, ':');
	path = make_path(path_split, cmd);
    if (!path)
    {
        printf("Could not find valid path for command\n");
        exit(1);
    }
    printf("Path: %s\n", path);
    // path[ft_strlen(path)] = '\0'; // add null terminator
    execve(path, cmd, envp);
    printf("Execve failed\n");
	int j = 0;
	while (cmd[j])
	{
		printf("arguments: %s\n", cmd[j]);
		j++;
	}
	// j = 0;
	// while (path_split[j])
	// {
	// 	printf("found path: %s\n", path_split[j]);
	// 	j++;
	// }
	// printf("%s\n", path);
	return (0);
}
