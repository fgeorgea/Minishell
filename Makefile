# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 17:02:21 by dopeyrat          #+#    #+#              #
#    Updated: 2023/05/02 15:00:45 by fgeorgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN			= main/
LEX				= lexer/
EXEC			= exec/
BUILTINS 		= builtins/
UTILS			= utils/
LINKED_LISTS	= linked_lists/

SRCS	=	$(MAIN)main.c \
			$(MAIN)free.c \
			$(MAIN)init.c \
			$(MAIN)error.c \
			$(EXEC)exec.c \
			$(EXEC)fork.c \
			$(EXEC)fork_utils.c \
			$(EXEC)free.c \
			$(EXEC)here_doc.c \
			$(EXEC)init.c \
			$(EXEC)init_utils.c \
			$(EXEC)parsing.c \
			$(EXEC)pipe.c \
			$(EXEC)utils.c \
			$(EXEC)pipex.c \
			$(EXEC)env.c \
			$(EXEC)redir.c \
			$(EXEC)protections.c \
			$(EXEC)debug.c \
			$(LINKED_LISTS)linked_list_env.c \
			$(BUILTINS)echo.c \
			$(BUILTINS)env.c \
			$(BUILTINS)pwd.c \
			$(BUILTINS)cd.c \
			$(BUILTINS)unset.c \
			$(UTILS)string_utils.c \
			$(UTILS)split_exit.c \
			$(LEX)lexer.c \
			$(LEX)lexer_utils.c \
			$(LEX)shell_split.c \
			$(LEX)tokenize.c \

OBJS	=	${SRCS:.c=.o}

NAME	= minishell

LIBFT	= LIBFT/libft.a

CC		= gcc

READL	= -L/usr/local/lib -I/usr/local/include -lreadline -L $(shell brew --prefix readline)/lib -I $(shell brew --prefix readline)/include

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

$(LIBFT):
	make -C LIBFT/

${NAME}:	$(LIBFT) ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} -ILIBFT -LLIBFT -lft ${READL} ${OBJS}

clean:
	rm -f ${OBJS}
	make -C LIBFT/ clean

fclean:	clean
	rm -f ${NAME}
	make -C LIBFT/ fclean

re:	fclean all

.PHONY:	re clean fclean all libft
