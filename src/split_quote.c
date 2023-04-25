/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_quote.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 15:59:22 by adri          #+#    #+#                 */
/*   Updated: 2023/04/25 22:44:23 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	neo_strlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**check_cmd(char *argv)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (!argv || !*argv)
		error_msg("", 0, 0);
	while (argv[i] && argv[i] != '\'' && argv[i] != '"')
		i++;
	if (argv[i] == '"' || argv[i] == '\'')
	{
		j = i + 1;
		while (argv[j] && argv[j] != argv[i])
			j++;
		if (!argv[j])
			error_msg("unmatched quote", 0, 0);
		tmp = split_quotes(tmp, argv);
		return (tmp);
	}
	else
	{
		tmp = ft_split(argv, ' ');
		return (tmp);
	}
}

char	**split_quotes(char **tmp, char *cmd)
{
	int		i;
	int		j;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		while (cmd[i] == ' ' && cmd[i + 1] != '\0')
			i++;
		i++;
	}
	tmp[0] = ft_strndup(cmd, (size_t)i);
	if (!tmp[0])
		return (NULL);
	i += 2;
	j = neo_strlen(cmd + i, cmd[i - 1]);
	tmp[1] = ft_strndup(cmd + i, (size_t)(j));
	if (!tmp[1])
		return (NULL);
	tmp[2] = NULL;
	return (tmp);
}
