/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:42:18 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/16 13:43:28 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_till_quote(char *str, char **result, int *i, int *j)
{
	while (str[*i] && str[*i] != '\"')
		(*result)[++(*j)] = str[(*i)++];
}

void	quote3(char ***arr, int *i, int *j, bool *quote)
{
	if ((*arr)[0][(*i)] && (*arr)[0][(*i)] == '\"' && (!(*arr)[0][(*i) + 1]
			|| (*arr)[0][(*i) + 1]) && (*arr)[0][(*i) + 1] != '\"')
	{
		((*arr)[1])[++(*j)] = (*arr)[0][(*i)++];
		*quote = !(*quote);
	}
	else if ((*arr)[0][(*i)] && (*arr)[0][(*i)] == '\"' && (!(*arr)[0][(*i) + 1]
			|| (*arr)[0][(*i) + 1]) && (*arr)[0][(*i) + 1] == '\"')
	{
		*i = *i + 2;
		copy_till_quote((*arr)[0], &(*arr)[1], i, j);
	}
}

void	rm_quote2(char ***arr, int i, bool quote)
{
	int	j;

	j = -1;
	while ((*arr)[0][i])
	{
		if ((*arr)[0][i] && (*arr)[0][i] == '\"')
		{
			if (!quote)
			{
				quote = !quote;
				((*arr)[1])[++j] = (*arr)[0][i++];
				copy_till_quote((*arr)[0], &(*arr)[1], &i, &j);
			}
			quote3(arr, &i, &j, &quote);
		}
		else
			copy_till_quote((*arr)[0], &(*arr)[1], &i, &j);
	}
}

void	rm_quote(t_data **data)
{
	char	**arr;
	int		i;
	bool	quote_started;

	printf("%s\n",(*data)->copy_input);

	arr = ft_calloc(3, sizeof(char *));
	arr[0] = ft_strdup((*data)->copy_input);
	arr[1] = ft_calloc(ft_strlen(arr[0]) + 1, sizeof(char));
	i = 0;
	quote_started = false;
	rm_quote2(&arr, i, quote_started);
	free((*data)->copy_input);
	(*data)->copy_input = ft_strdup(arr[1]);
	printf("%s\n",(*data)->copy_input);
	free_db_array(&arr);
}
