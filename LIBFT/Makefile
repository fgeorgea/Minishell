# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 12:36:28 by dpeyrat           #+#    #+#              #
#    Updated: 2023/02/07 12:37:45 by dopeyrat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= BASIC/ft_atoi.c BASIC/ft_bzero.c BASIC/ft_calloc.c BASIC/ft_isalnum.c BASIC/ft_isalpha.c BASIC/ft_isascii.c BASIC/ft_isdigit.c BASIC/ft_isprint.c BASIC/ft_itoa.c BASIC/ft_lstadd_back.c BASIC/ft_lstadd_front.c BASIC/ft_lstclear.c BASIC/ft_lstdelone.c BASIC/ft_lstiter.c BASIC/ft_lstlast.c BASIC/ft_lstmap.c BASIC/ft_lstnew.c BASIC/ft_lstsize.c BASIC/ft_memchr.c BASIC/ft_memcmp.c BASIC/ft_memcpy.c BASIC/ft_memmove.c BASIC/ft_memset.c BASIC/ft_putchar_fd.c BASIC/ft_putendl_fd.c BASIC/ft_putnbr_fd.c BASIC/ft_putstr_fd.c BASIC/ft_split.c BASIC/ft_strchr.c BASIC/ft_strdup.c BASIC/ft_strjoin.c BASIC/ft_strlcat.c BASIC/ft_strlcpy.c BASIC/ft_strlen.c BASIC/ft_strmapi.c BASIC/ft_strncmp.c BASIC/ft_strnstr.c BASIC/ft_strrchr.c BASIC/ft_strtrim.c BASIC/ft_substr.c BASIC/ft_tolower.c BASIC/ft_toupper.c BASIC/ft_striteri.c

PRINTF	= FT_PRINTF/ft_printf.c FT_PRINTF/ft_printf_utils.c FT_PRINTF/get_conv.c FT_PRINTF/CHAR/convert_char.c FT_PRINTF/INT/convert_addr.c FT_PRINTF/INT/convert_int.c FT_PRINTF/INT/convert_uint.c

GNL		= GNL/get_next_line.c

OBJS	= ${SRCS:.c=.o}

P_OBJS	= ${PRINTF:.c=.o}

G_OBJS	= ${GNL:.c=.o}

NAME	= libft.a

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} ${P_OBJS} ${G_OBJS}
	@ar rc ${NAME} ${OBJS} ${P_OBJS} ${G_OBJS}
	@ranlib ${NAME}

clean:
		@rm -f ${OBJS} ${P_OBJS} ${G_OBJS}

fclean:		clean
		@rm -f ${NAME}

re:			fclean all

.PHONY:		re clean fclean all
