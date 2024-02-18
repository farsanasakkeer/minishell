/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:40:29 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/15 13:49:47 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_db_array(char ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		free((*str)[i]);
	free(*str);
}

void	free_tokens(t_data **data)
{
	int	t_len;
	int	i;

	t_len = (*data)->tokens[0].tok_len;
	i = -1;
	while (++i < t_len && (*data)->tokens[i].value)
		free((*data)->tokens[i].value);
	free((*data)->tokens);
}

void	perror_free(t_data **data, char *str, char *value, int free_only)
{
	if (!free_only)
	{
		
		ft_putstr_fd("\x1b[31m", STDERR_FILENO);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("\'\n", 2);
		ft_putstr_fd("\x1b[0m", STDERR_FILENO);
		(*data)->exit_status = 2;
	}
	free((*data)->input);
	free((*data)->copy_input);
	free((*data)->path);
	free_tokens(data);
}

void	print_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd("\x1b[31m", STDERR_FILENO);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	perror("");
	ft_putstr_fd("\x1b[0m", STDERR_FILENO);
}
