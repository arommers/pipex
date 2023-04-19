/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_quote.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 15:59:22 by adri          #+#    #+#                 */
/*   Updated: 2023/04/19 10:26:54 by arommers      ########   odam.nl         */
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

char	**check_cmd(t_data *data, char *argv)
{
	int	i;
	int	j;

	i = 0;
	if (!argv || !*argv)
		error_msg("not good", 0);
	while (argv[i] && argv[i] != '\'' && argv[i] != '"')
		i++;
	if (argv[i] == '"' || argv[i] == '\'')
	{
		j = i + 1;
		while (argv[j] && argv[j] != argv[i])
			j++;
		if (!argv[j])
			error_msg("unmatched quote", 0);
		return (split_quotes(data, argv));
	}
	else
		return (ft_split(argv, ' '));
}

char	**split_quotes(t_data *data, char *cmd)
{
	int		i;
	int		j;

	data->args = malloc(sizeof(char *) * 3);
	if (!data->args)
		return (NULL);
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	data->args[0] = ft_strndup(cmd, (size_t)i);
	if (!data->args[0])
		return (NULL);
	i += 2;
	j = neo_strlen(cmd + i, cmd[i - 1]);
	data->args[1] = ft_strndup(cmd + i, (size_t)(j));
	if (!data->args[1])
		return (NULL);
	data->args[2] = NULL;
	return (data->args);
}
