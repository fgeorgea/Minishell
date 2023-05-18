/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/18 19:43:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*********************    INCLUDES    ************************/

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include "LIBFT/libft.h"
# include "structs.h"
# include "exec/pipex.h"
# include "lexer/lexer.h"
# include "builtins/builtins.h"
# include "linked_lists/linked_lists.h"
# include "sig/sig.h"

/*********************    MACROS       ************************/

# define EXIT_MALLOC_FAILURE 2
# define EXIT_SIGNAL_FAILURE 3

// PIPE MODE
# define OUT 0
# define OUT_APP 1
# define IN 2
# define HEREDOC 3
# define HEREDOC_EXP 4

# ifdef NULL
#  undef NULL  
#  define NULL 0
# else
#  define NULL 0
# endif

/*********************      STRUCTS    ************************/

t_shell	*g_sh;

/*********************    FUNCTIONS    ************************/

char	*readline(const char *prompt);
void	rl_replace_line(const char *text, int clear_undo);
void	init_shell(char **argv, char **env);
int		init_signals(void);
void	ft_free_env(void);
void	ft_free_global(void);
void	ft_exit(int status);
void	print_err(const char *cmd, const char *input, const char *message);
void	lexer(char *str);
int		skip_quotes(char *str, int i);
int		get_next_pipe(char *str, int i);
char	**shell_split(char *str, char *sep, int s);
void	ft_free_cmd(void);

#endif
