/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:54:37 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/16 18:07:58 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote_cwd(t_data **data, int i)
{
	char	*str;
	char	*temp;

	str = ft_strdup((*data)->tokens[i + 1].value);
	//quote removing of 'txt.txt'
	if ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		|| (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
	{
		free(str);
		str = ft_substr((*data)->tokens[i + 1].value, 1,
				ft_strlen((*data)->tokens[i + 1].value) - 2);
	}
	if (ft_strncmp(str, "./", 2) == 0)
	{
		temp = ft_substr(str, 2, ft_strlen(str) - 2);
		free(str);
		str = temp;
	}
	return (str);
}

int	check_dir_existance(t_data **data, t_token *tokens, int i, char *str)
{
	bool	is_pipe;

	is_pipe = true;
	while (++i < tokens[0].tok_len - 1)
	{
		if (tokens[i].type == PIPE)
			is_pipe = true;
		if (tokens[i].type == LESS || tokens[i].type == GREAT
			|| tokens[i].type == GREAT_GREAT)
		{
			str = remove_quote_cwd(data, i);
			printf("%s\n",str);
			if (!is_directory((*data)->no_of_pipes, str,
					tokens[i].type, &is_pipe))
			{
				free(str);
				perror_free(data, " ", " ", 1);
				return (0);
			}

		}
	}
	return (1);
}

int	lex(t_data **data)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	build_tokens(data);
	count_pipes(data, (*data)->tokens);
	if (!syntax_errors(data, (*data)->tokens, (*data)->tokens[0].tok_len))
		return (0);
	if (!check_dir_existance(data, (*data)->tokens, i, str))
	{
		(*data)->exit_status = 1;
		return (0);
	}
	return (1);
}