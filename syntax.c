/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:27:10 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/12 13:22:18 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_cmd_exist(t_data **data, t_token *tokens, int i)
{
	int	cmd_exist;
	int	pipes;

	i = -1;
	pipes = -1;
	if ((*data)->tokens[tokens[0].tok_len - 1].type == PIPE)
		return (perror_free(data,
				" syntax error near unexpected token `", "|", 0), 0);
	while ((*data)->no_of_pipes > pipes)
	{
		cmd_exist = 0;
		while (++i <= tokens[0].tok_len && tokens[i].type != PIPE)
		{
			if (tokens[i].type == B_COMMAND || tokens[i].type == UNKNOWN 
				|| tokens[i].type == DELIMITER)
				cmd_exist = 1;
		}
		if (!cmd_exist)
			return (perror_free(data,
					" syntax error near unexpected token `", "|", 0), 0);
		pipes++;
	}
	return (1);
}

int	check_syntax_error2(t_data **data, t_token *tokens, int i)
{
	t_tokenstype	type;
	t_tokenstype	type2;

	i = -1;
	while (++i < tokens[0].tok_len)
	{
		type = tokens[i].type;
		if (tokens[i + 1].value)
			type2 = tokens[i + 1].type;
		else
			return (1);
		if (type == GREAT || type == GREAT_GREAT
			|| type == LESS_LESS || type == LESS)
		{
			if (type2 == GREAT || type2 == GREAT_GREAT
				|| type2 == LESS_LESS || type2 == LESS || type2 == PIPE)
			{
				perror_free(data, " syntax error near unexpected token `",
					tokens[i + 1].value, 0);
				(*data)->exit_status = 258;
				return (0);
			}
		}
	}
	return (1);
}


int	syntax_errors(t_data **data, t_token *tokens, int i)
{
	i = -1;
	if (tokens[0].value && tokens[0].value[0] == ';')
		return (perror_free(data, " syntax error near unexpected token `", ";", 0), 0);
	if ((*data)->tokens[tokens[0].tok_len - 1].type == GREAT
		|| (*data)->tokens[tokens[0].tok_len - 1].type == GREAT_GREAT
		|| (*data)->tokens[tokens[0].tok_len - 1].type == LESS
		|| (*data)->tokens[tokens[0].tok_len - 1].type == LESS_LESS)
		return (perror_free(data," syntax error near unexpected token `","newline", 0), 0);
	if (!check_cmd_exist(data, tokens, i))
		return (0);
	while (++i < tokens[0].tok_len)
	{
		if (tokens[i].value[0] == ';' || tokens[i].value[0] == '\\')
			return (perror_free(data, 
					"Outside project scope ", "\\", 0), 0);
	}
	if (!check_syntax_error2(data, tokens, i))
		return (0);
	return (1);
}
