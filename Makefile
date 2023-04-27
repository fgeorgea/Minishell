# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 17:02:21 by dopeyrat          #+#    #+#              #
#    Updated: 2023/04/27 15:22:27 by fgeorgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

<<<<<<< HEAD
EXEC_DIR	= exec/
MAIN_DIR	= main/
LEX_DIR		= lexer/
=======
NAME	= minishell

EXEC_DIR = exec/
MAIN_DIR = main/
>>>>>>> 2eda31ccfa8eccd915d18e3fe9fa196d1411dfce

SRCS	=	$(MAIN_DIR)main.c \
			$(MAIN_DIR)free.c \
			$(MAIN_DIR)init.c \
			$(MAIN_DIR)error.c \
			$(EXEC_DIR)chained_list.c \
			$(EXEC_DIR)error.c \
			$(EXEC_DIR)exec.c \
			$(EXEC_DIR)fork.c \
			$(EXEC_DIR)fork_utils.c \
			$(EXEC_DIR)free.c \
			$(EXEC_DIR)here_doc.c \
			$(EXEC_DIR)init.c \
			$(EXEC_DIR)init_utils.c \
			$(EXEC_DIR)parsing.c \
			$(EXEC_DIR)pipe.c \
			$(EXEC_DIR)utils.c \
			$(EXEC_DIR)pipex.c \
			$(EXEC_DIR)env.c \
			$(LEX_DIR)lexer_utils.c \
			$(LEX_DIR)lexer.c \
			$(LEX_DIR)shell_split.c \

OBJS	=	${SRCS:.c=.o}


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
