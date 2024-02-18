/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:53:01 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/16 19:45:34 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_controller(int sig_num)
{
	if (sig_num == SIGINT)
	{
		if (waitpid(-1, &g_exit_status, WNOHANG) == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_exit_status = 1;
		}
	}
}

// void	child_signal_handler(int num)
// {
// 	if (num == SIGINT)
// 		write(1, "\n", 1);
// 	else if (num == SIGQUIT)
// 		ft_putstr_fd("Quit: 3\n", 2);
// }

// void	sigint_here_doc_handler(int sig)
// {
// 	int	fd;

// 	fd = 0;
// 	g_exit_status = EXIT_HERE_DOC;
// 	(void)sig;
// 	fd = open("libft/here_doc_sig", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	dup2(fd, STDIN_FILENO);
// 	write(fd, "\n\n", 2);
// 	close(fd);
// }

// void	child_signals(t_command *cmd)
// {
// 	if (ft_strcmp(cmd->input.name, "here_doc") != 0)
// 	{
// 		signal(SIGINT, child_signal_handler);
// 		signal(SIGQUIT, child_signal_handler);
// 	}
// }

void	handle_signals(void)
{
	signal(SIGINT, signal_controller);
	signal(SIGQUIT, SIG_IGN);
}
