# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvaliyak <fvaliyak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 13:26:22 by fvaliyak          #+#    #+#              #
#    Updated: 2024/02/16 18:15:55 by fvaliyak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell
CC        := cc
FLAGS    := -Wall -Wextra -Werror -g -fsanitize=address -g3#-lreadlin

LIBS = -lreadline 

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      init.c \
                          lexer.c \
                          lexer1.c \
                          libft/ft_atoi.c \
                          libft/ft_bzero.c \
                          libft/ft_calloc.c \
                          libft/ft_isalnum.c \
                          libft/ft_isalpha.c \
                          libft/ft_isascii.c \
                          libft/ft_isdigit.c \
                          libft/ft_isprint.c \
                          libft/ft_itoa.c \
                          libft/ft_lstadd_back.c \
                          libft/ft_lstadd_front.c \
                          libft/ft_lstclear.c \
                          libft/ft_lstdelone.c \
                          libft/ft_lstiter.c \
                          libft/ft_lstlast.c \
                          libft/ft_lstmap.c \
                          libft/ft_lstnew.c \
                          libft/ft_lstsize.c \
                          libft/ft_memchr.c \
                          libft/ft_memcmp.c \
                          libft/ft_memcpy.c \
                          libft/ft_memmove.c \
                          libft/ft_memset.c \
                          libft/ft_printf.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_split.c \
                          libft/ft_strchr.c \
                          libft/ft_strcmp.c \
                          libft/ft_strdup.c \
                          libft/ft_striteri.c \
                          libft/ft_strjoin.c \
                          libft/ft_strlcat.c \
                          libft/ft_strlcpy.c \
                          libft/ft_strlen.c \
                          libft/ft_strmapi.c \
                          libft/ft_strncmp.c \
                          libft/ft_strnstr.c \
                          libft/ft_strrchr.c \
                          libft/ft_strtrim.c \
                          libft/ft_substr.c \
                          libft/ft_tolower.c \
                          libft/ft_toupper.c \
                          libft/get_next_line.c \
                          libft/utils.c \
                          main.c \
                          separate_char.c \
                          space_quote.c \
						  free.c \
						  token.c \
						  sig_handler.c \
						  syntax.c \
						  quote.c \
						  dir.c \
						  parser.c \
                          


OBJS        := $(SRCS:.c=.o)
				
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}
	@echo "$(GREEN).\c${CLR_RMV}"

################################################################################
#                                  Makefile  objs                              #
################################################################################



${NAME}:	${OBJS}
			@${CC} ${FLAGS} $(LIBS) -o ${NAME} ${OBJS}
			@echo "$(YELLOW)"
			@echo "#     # ### #     # ###  #####  #     # ####### #       #      "
			@echo "##   ##  #  ##    #  #  #     # #     # #       #       #       "
			@echo "# # # #  #  # #   #  #  #       #     # #       #       #       "
			@echo "#  #  #  #  #  #  #  #   #####  ####### #####   #       #       "
			@echo "#     #  #  #   # #  #        # #     # #       #       #       "
			@echo "#     #  #  #    ##  #  #     # #     # #       #       #       "
			@echo "#     # ### #     # ###  #####  #     # ####### ####### ####### ${CLR_RMV}"
			@echo "$(GREEN).......................................................... ${CLR_RMV}"


all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


