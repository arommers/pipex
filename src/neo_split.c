/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   neo_split.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 15:59:22 by adri          #+#    #+#                 */
/*   Updated: 2023/04/13 16:41:34 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	neo_strlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		write(2, "\n", 1);
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
		error_msg("not good");
	while (argv[i] && argv[i] != '\'' && argv[i] != '"')
		i++;
	if (argv[i] == '"' || argv[i] == '\'')
	{
		j = i + 1;
		while (argv[j] && argv[j] != argv[i])
			j++;
		if (!argv[j])
			error_msg("unmatched quote");
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
	// j = i;
	// while (cmd[j])
	// {
	// 	j++;
	// 	if (cmd[j] == cmd[i])
	// 		data->args[1] = ft_strndup(cmd + i, j - i);
	// 	else
	// 		data->args[1] = NULL;
	// }
	data->args[2] = NULL;
	int k = 0;
	while (data->args[k])
	{
    	int l = 0;
    	while (data->args[k][l])
    	{
        	write(2, &data->args[k][l], 1);
        	l++;
    	}
    	write(2, "\n", 1);  // add a newline after each row
    	k++;
	}
	return (data->args);
}

// int	neo_strlen(const char *str, char c, char quote_type, int in_quotes)
// {
// 	int	i;

// 	i = 0;
// 	if (in_quotes == 0)
// 	{
// 		while (str[i] && str[i] != c)
// 			i++;
// 	}
// 	else
// 		while (str[i] && str[i] != quote_type)
// 			i++;
// 	return (i);
// }


// int	is_quote(char c)
// {
// 	if (c == '"' || c == '\'')
// 		return (1);
// 	return (0);
// }

// int	is_in_quotes(char c, int in_quotes, char quote_type)
// {
// 	if (is_quote(c))
// 	{
// 		if (!in_quotes)
// 		{
// 			in_quotes = 1;
// 			quote_type = c;
// 		}
// 		else if (c == quote_type)
// 			in_quotes = 0;
// 	}
// 	return (in_quotes);
// }

// char	**neo_split(char const *s, char c)
// {
// 	char	**new;
// 	int		i;
// 	int		in_quotes;
// 	char	quote_type;

// 	i = 0;
// 	in_quotes = 0;
// 	quote_type = '\0';
// 	new = (char **)malloc(sizeof(char *) * (ft_get_rows(s, c) + 1));
// 	if (!new)
// 		return (NULL);
// 	while (*s)
// 	{
// 		in_quotes = is_in_quotes(*s, in_quotes, quote_type);
// 		if (*s != c || in_quotes)
// 		{
// 			if (is_quote(*s))
// 			{
// 				quote_type = *s;
// 				new[i++] = ft_substr(s + 1, 0, neo_strlen(s + 1, c, quote_type, 1));
// 				s += neo_strlen(s + 1, c, quote_type, 1) + 2;
// 			}
// 			else
// 			{
// 				new[i++] = ft_substr(s, 0, neo_strlen(s, c, '\0', 0));
// 				s += neo_strlen(s, c, '\0', 0);
// 			}
// 			if (!new[i - 1])
// 				return (ft_free(new));
// 		}
// 		else
// 			s++;
// 	}
// 	new[i] = NULL;
// 	return (new);
// }

// char	**neo_split(char const *s, char c)
// {
// 	char	**new;
// 	int		i;
// 	int		in_quotes;
// 	char	quote_type;

// 	i = 0;
// 	in_quotes = 0;
//     quote_type = '\0';
// 	new = (char **)malloc(sizeof(char *) * (ft_get_rows(s, c) + 1));
// 	if (!new)
// 		return (NULL);
// 	while (*s)
// 	{
// 		in_quotes = is_in_quotes(*s, in_quotes, quote_type);
// 		if (*s != c || in_quotes)
// 		{
// 			new[i++] = ft_substr(s, 0, neo_strlen(s, c, in_quotes, quote_type));
// 			if (!new[i - 1])
// 				return (ft_free(new));
// 			s += neo_strlen(s, c, in_quotes, quote_type);
// 		}
// 		else
// 			s++;
// 	}
// 	new[i] = NULL;
// 	return (new);
// }
