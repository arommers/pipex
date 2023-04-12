/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   neo_split.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 15:59:22 by adri          #+#    #+#                 */
/*   Updated: 2023/04/11 15:07:45 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	neo_strlen(const char *str, char c, char quote_type, int in_quotes)
{
	int i;

	i = 0;
    if (in_quotes == 0)
    {
        while (str[i] && str[i] != c)
        	i++;
    }
    else
        while (str[i] && str[i] != quote_type) 
        	i++;
	return (i);
}


int	is_quote(char c)
{
	if (c == '"' || c == '\'')
        return (1);
    return (0);
}

int	is_in_quotes(char c, int in_quotes, char quote_type)
{
	if (is_quote(c))
	{
		if (!in_quotes)
		{
			in_quotes = 1;
			quote_type = c;
		}
		else if (c == quote_type)
			in_quotes = 0;
	}
	return (in_quotes);
}

char	**neo_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		in_quotes;
	char	quote_type;

	i = 0;
	in_quotes = 0;
    quote_type = '\0';
	new = (char **)malloc(sizeof(char *) * (ft_get_rows(s, c) + 1));
	if (!new)
		return (NULL);
	while (*s)
	{
		in_quotes = is_in_quotes(*s, in_quotes, quote_type);
		if (*s != c || in_quotes)
		{
			if (is_quote(*s))
			{
				quote_type = *s;
				new[i++] = ft_substr(s + 1, 0, neo_strlen(s + 1, c, quote_type, 1));
				s += neo_strlen(s + 1, c, quote_type, 1) + 2;
			}
			else
			{
				new[i++] = ft_substr(s, 0, neo_strlen(s, c, '\0', 0));
				s += neo_strlen(s, c, '\0', 0);
			}
			if (!new[i - 1])
				return (ft_free(new));
		}
		else
			s++;
	}
	new[i] = NULL;
	return (new);
}

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
