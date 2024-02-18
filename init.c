/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:19:20 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/16 19:48:32 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_status(t_data **data)
{
	if (g_exit_status != -2)
	{
		(*data)->exit_status = g_exit_status;
		g_exit_status = -2;
	}
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!cpy)
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}

int	only_space(char *input, t_data **data)
{
	int	i;
	
	i = 0;
	while (input[i] && (input[i] == 32 || (input[i] >= 9 && input[i] <= 13)))
		i++;
	if (!input[i])
	{
		free((*data)->input);
		return (1);
	}
	return (0);
}

int	init_data(t_data **data)
{
	int	i;
	
	printf("\033[1;34m");
	(*data)->input =  readline("minishell>> \033[0m");
	if ((*data)->input == NULL)
	{
		free((*data)->input);
		free_db_array(&(*data)->env);
		free (*data);
		printf("exit\n");
		exit (0);
	}
	check_exit_status(data);	
	if (only_space((*data)->input, data))
		return (0);
	add_history((*data)->input);
	(*data)->copy_input = ft_strdup((*data)->input);
	// (*data)->command = NULL;
	(*data)->no_of_pipes = 0;
	// (*data)->input_fd = -1;
	(*data)->path = NULL;
	i = -1;
	printf("env:%s\n",(*data)->env[0]);
	while ((*data)->env[++i])
		if (ft_strncmp((*data)->env[i], "PATH", 4) == 0)
			(*data)->path = strdup((*data)->env[i]);
	return (1);
}