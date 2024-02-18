/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:15:51 by fvaliyak          #+#    #+#             */
/*   Updated: 2024/02/16 19:50:51 by fvaliyak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <stdbool.h>
# include <dirent.h>
# include "libft/libft.h"

int	g_exit_status;

typedef enum s_tokenstype
{
	NONE = -1,
	B_COMMAND,
	PIPE,
	GREAT,
	LESS,
	GREAT_GREAT,
	LESS_LESS,
	UNKNOWN,
	DELIMITER,
	
}	t_tokenstype;

typedef struct s_token
{
	t_tokenstype	type;
	int				tok_no;
	int				tok_len;
	char			*value;
}	t_token;

typedef struct s_data
{
	char		*input;
	char		**env;
	char		*copy_input;
	int			no_of_pipes;
	char		*path;
	int			input_fd;
	t_token		*tokens;
	int			exit_status;
	char		**splitted_path;
}t_data;






// init.c
char		**copy_env(char **envp, int add);
int			only_space(char *input, t_data **data);
int			init_data(t_data **data);
void		check_exit_status(t_data **data);

// space_quote.c
bool		handle_db_quotes(t_data **data);
void		handle_extra_spaces(char **copy_of_input, t_data **data);
char		*remove_extra_space_2(char **input, char **result, int j);
int			if_quote(char **input, char **result, int *j, int *i);

//seperate_char.c
int			separate_characters(t_data **data, char	**input);
void		separate_characters_utils(char *input, int *i, int *j, char **result);
void		separate(char **result, char *input, int *i, int *j);

void		mini_loop(t_data **data);
int			main(int argc, char **argv, char **env);
void		increment_shlvl(t_data **data);

//lexer.c
int			lex(t_data **data);
char		*remove_quote_cwd(t_data **data, int i);
int			check_dir_existance(t_data **data, t_token *tokens, int i, char *str);

//lexer1.c
char		**split_input(char *str, char c);
void		splitting(char *str, int i, char ***strings, char c);
char		*ft_word(char *str, char c);
int			count_strings(char *str, char c);
int			len_inside_quote(char *str, int i, char c);

//token.c
int			len_splitted(char **splitted);
void		count_pipes(t_data **data, t_token *tokens);
void		check_capitals(t_token *token, char **splitted, int tok_no);
void		get_tokentype(t_token *token, char **splitted, int tok_no);
void		build_tokens(t_data **data);

//syntax.c
int			syntax_errors(t_data **data, t_token *tokens, int i);
int			check_syntax_error2(t_data **data, t_token *tokens, int i);
int			check_cmd_exist(t_data **data, t_token *tokens, int i);

//free.c
void		free_db_array(char ***str);
void		free_tokens(t_data **data);
void		perror_free(t_data **data, char *str, char *value, int free_only);
void		print_error(char *s1, char *s2, char *s3);


// quote.c
void		copy_till_quote(char *str, char **result, int *i, int *j);
void		quote3(char ***arr, int *i, int *j, bool *quote);
void		rm_quote2(char ***arr, int i, bool quote);
void		rm_quote(t_data **data);

// dir.c
int			is_directory(int count_pipes, char *str, t_tokenstype type, bool *is_pipe);
char		*get_directory(char *value);


// parser.c
int	parser(t_data **data);

void	handle_signals(void);
void	signal_controller(int sig_num);
#endif