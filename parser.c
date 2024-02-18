/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:11:58 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/18 21:04:56 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_executable(char *str)
{
	int	is_error;

	is_error = 0;
	errno = 0;
	if (ft_strncmp(str, "./", 2) == 0) //input string starts with './' or '/'
	{
		if (access(str, X_OK) == 0)
			return (1);
		else
		{
			is_error = -1;
			print_error("minishell: ", str, ": ");
		}
	}
	else if (ft_strchr(str, '/'))
	{
		if (access(str, X_OK) == 0)
			return (1);
		else
		{
			is_error = -1;
			print_error("minishell: ", str, ": ");
		}
	}
	return (is_error);
}

char	*get_full_path(char *dir, char *command, char *fullPath)
{
	int	dir_len;

	dir_len = ft_strlen(dir);
	fullPath = (char *)malloc((ft_strlen(dir) + 1) * sizeof(char));
	fullPath[ft_strlen(dir)] = '\0';
	fullPath = (char *)ft_memcpy(fullPath, dir, ft_strlen(dir));
	if (dir[dir_len - 1] != '/')
		fullPath = ft_strjoin(fullPath, "/");
	fullPath = ft_strjoin(fullPath, command);
	return (fullPath);
}

int	find_command(t_data **data, char *str)
{
	int		i;
	char	*full_path;

	i = -1;
	full_path = NULL;
	while ((*data)->splitted_path && (*data)->splitted_path[++i])
	{
		full_path = get_full_path((*data)->splitted_path[i], str, full_path);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				free(full_path);
				return (1);
			}
			else
			{
				print_error("minishell: ", full_path, ": ");
				free(full_path);
				return (-2);
			}
		}
		free(full_path);
	}
	return (0);
}

int	is_non_b_command(char *str, t_data **data, int count_pipes)
{
	int	is_cmd_valid;
	int	is_executable;

	is_executable = is_cmd_executable(str);
	if (is_executable == -1 && count_pipes <= 0)
		return (-2);
	else if (is_executable == 1)
		return (1);
	is_cmd_valid = find_command(data, str);
	if (is_cmd_valid == 1)
		return (1);
	else if (is_cmd_valid == -2)
		return (-2);
	return (0);
}


int	cmd_present(t_data **data, int i, int token_len)
{
	if ((*data)->tokens[i].type == PIPE && i > 0)
	{
		if (++i >= token_len)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			(*data)->exit_status = 2;
			return (0);
		}
	}



	
}

int	command_existance(t_data **data, int i, int token_len)
{
	int		temp;

	while (++i < token_len)
	{
		if ((i == 0 || (*data)->tokens[i].type == PIPE))
		{
			temp = cmd_present(data, i, token_len);

			
		}
	}
	return (1);


}

int	parser(t_data **data)
{
	// int			i;
	int			token_len;
	// char		*arg;

	token_len = (*data)->tokens[0].tok_len;
	(*data)->splitted_path = ft_split((*data)->path, ':');
	int i = 0;
	while ((*data)->splitted_path[i])
	{
		printf("%d\n",i);
		printf("splitted path:%s\n",(*data)->splitted_path[i++]);
	}
	


	return (1);
}