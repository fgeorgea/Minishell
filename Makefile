# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 17:02:21 by dopeyrat          #+#    #+#              #
#    Updated: 2023/05/29 20:27:57 by fgeorgea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN			= main/
LEX				= lexer/
EXEC			= exec/
BUILTINS 		= builtins/
LINKED_LISTS	= linked_lists/
SIG				= sig/

SRCS	=	$(MAIN)main.c \
			$(MAIN)free.c \
			$(MAIN)init.c \
			$(MAIN)init_utils.c \
			$(MAIN)error.c \
			$(EXEC)exec.c \
			$(EXEC)wait.c \
			$(EXEC)exec_utils.c \
			$(EXEC)fork.c \
			$(EXEC)link_fd.c \
			$(EXEC)free.c \
			$(EXEC)here_doc.c \
			$(EXEC)init.c \
			$(EXEC)parse_cmd.c \
			$(EXEC)parse_cmd_err.c \
			$(EXEC)pipe.c \
			$(EXEC)close_pipes.c \
			$(EXEC)utils.c \
			$(EXEC)pipex.c \
			$(EXEC)env.c \
			$(EXEC)redir.c \
			$(EXEC)redir_utils.c \
			$(EXEC)protections.c \
			$(EXEC)expand_heredoc.c \
			$(EXEC)underscore_utils.c \
			$(LINKED_LISTS)linked_list_env.c \
			$(LINKED_LISTS)linked_list_cmd.c \
			$(BUILTINS)echo.c \
			$(BUILTINS)env.c \
			$(BUILTINS)pwd.c \
			$(BUILTINS)cd.c \
			$(BUILTINS)cd_utils.c \
			$(BUILTINS)unset.c \
			$(BUILTINS)export.c \
			$(BUILTINS)export_utils.c \
			$(BUILTINS)call_builtin.c \
			$(BUILTINS)redirections_builtins.c \
			$(BUILTINS)restore_stdout.c \
			$(BUILTINS)exit.c \
			$(BUILTINS)exit_utils.c \
			$(LEX)lexer.c \
			$(LEX)lexer_utils.c \
			$(LEX)shell_split.c \
			$(LEX)tokenize.c \
			$(LEX)expander.c \
			$(LEX)post_expander.c \
			$(LEX)remove_quotes.c \
			$(LEX)parser.c \
			$(LEX)new_expander.c \
			$(LEX)expander_utils.c \
			$(LEX)tokenize_utils.c \
			$(LEX)redir_parser.c \
			$(LEX)arg_parser.c \
			$(LEX)expand_trim_split.c \
			$(LEX)join_value_split.c \
			$(SIG)signal.c \

OBJS	=	${SRCS:.c=.o}

NAME	= minishell

LIBFT	= LIBFT/libft.a

CC		= gcc

READL	= -L/usr/local/lib -I/usr/local/include -lreadline -L $(shell brew --prefix readline)/lib -I $(shell brew --prefix readline)/include

CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

all:	${NAME}

$(LIBFT):
	make -C LIBFT/

${NAME}:	$(LIBFT) ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} -ILIBFT -LLIBFT -lft ${READL} ${OBJS}

clean:
	rm -rf ${OBJS}
	make -C LIBFT/ clean

fclean:	clean
	rm -rf ${NAME}
	make -C LIBFT/ fclean

re:	fclean all

.PHONY:	re clean fclean all