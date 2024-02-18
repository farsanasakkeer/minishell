/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:19:36 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/16 12:34:28 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_inside_quote(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	i++;
	return (i);
}

int	count_strings(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] != '\0')//after space, there is anything present it will be new string
			j++;
		if (str[i] == '\'')
			i = len_inside_quote(str, i, '\'');
		else if (str[i] == '\"')
			i = len_inside_quote(str, i, '\"');
		while (str[i] && str[i] != c)
			i++;
	}
	return (j);
}

char	*ft_word(char *str, char c)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	if (str[len] && (str[len] == '\''))
		len = len_inside_quote(str, len, '\'');
	else if (str[len] && (str[len] == '\"'))
		len = len_inside_quote(str, len, '\"');
	while (str[len] && str[len] != c)
		len++;
	word = ft_calloc((len + 1), sizeof(char));
	i = -1;
	while (++i < len)
		word[i] = str[i];
	return (word);
}

void	splitting(char *str, int i, char ***strings, char c)
{
	char	quote;

	while (*str != '\0')
	{
		while (*str != '\0' && *str == c)
			str ++;
		if (*str != '\0')
			(*strings)[i++] = ft_word(str, c);
		if (*str && (*str == '\'' || *str == '\"'))
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				str++;
		}
		while (*str && *str != c)
			str++;
	}
	(*strings)[i] = 0;
}

char	**split_input(char *str, char c)
{
	char	**strings;
	int		i;

	i = 0;
	if (!str)
		return (0);
	strings = malloc ((count_strings(str, c) + 1) * sizeof(char *));
	if (!strings)
		return (0);
	splitting(str, i, &strings, c);
	return (strings);
}