/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:04:33 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/16 18:09:00 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check2(char *str, char **directory, int count_pipes, bool *is_pipe)
{
	if (count_pipes >= 1 && (*is_pipe == true))
	{
		*is_pipe = false;
		free(*directory);
		return (print_error("minishel: ", str, ": "), 1);
	}
	else if (count_pipes == 0)
	{
		free(*directory);
		return (print_error("minishell: ", str, ": "), 0);
	}
	free(*directory);
	return (1);
}

static	int	check1(char *str, int count_pipes, bool *is_pipe)
{

	if (count_pipes >= 1 && *is_pipe == true) //we have to deal pipe remainings
	{
		*is_pipe = false;
		return (print_error("minishell: ", str, ": "), 1);
	}
	else if (count_pipes == 0)
		return (print_error("minishell: ", str, ": "), 0);
	return (1);
}

static	int	check3(char *str, char **directory, int count_pipes)
{
	int	fd;

	(void)count_pipes;
	fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd == -1)
	{
		print_error("minishell: ", str, ": ");
		close(fd);
		free(*directory);
		return (0);
	}
	close(fd);
	return (1);
}
char	*get_directory(char *value)
{
	int	str_len;

	str_len = ft_strlen(value);
	while (str_len > 0 && value[--str_len] != '/')
		continue ;
	return (ft_substr(value, 0, str_len));
}

int	is_directory(int count_pipes, char *str, t_tokenstype type, bool *is_pipe)
{
	char	*directory;
	
	if (type == LESS && access(str, R_OK) == -1) //access denied
		return (check1(str, count_pipes, is_pipe));
	directory = get_directory(str);
	if (ft_strchr(str, '/') && (type == GREAT || type == GREAT_GREAT)
		&& access(directory, F_OK) == -1)
		return (check2(str, &directory, count_pipes, is_pipe) == 1);
	else if (type == GREAT || type == GREAT_GREAT)
		if (check3(str, &directory, count_pipes) == 0)
			return (0);
	free(directory);
	return (1);
}
