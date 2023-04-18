# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 17:02:21 by dopeyrat          #+#    #+#              #
#    Updated: 2023/03/15 12:22:39 by dopeyrat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c

OBJS	=	${SRCS:.c=.o}

NAME	= minishell

LIBFT	= LIBFT/libft.a

CC		= gcc

READL	= -L/usr/local/lib -I/usr/local/include -lreadline -L $(shell brew --prefix readline)/lib -I $(shell brew --prefix readline)/include

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

${NAME}:	${OBJS} ${LIBFT}
	${CC} -o ${NAME} ${OBJS} ${CFLAGS} ${READL}

${LIBFT}:
	make -C LIBFT

clean:
	rm -f ${OBJS}
	make clean -C LIBFT

fclean:	clean
	rm -f ${NAME}
	make fclean -C LIBFT

re:	fclean all

.PHONY:	re clean fclean all
