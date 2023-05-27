/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/27 18:45:17 by fgeorgea         ###   ########.fr       */
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

// PROMPT COLORS
# define BLUE "\033[0;94m"
# define RED "\033[0;91m"
# define ENDC "\033[0;39m"

/*********************      STRUCTS    ************************/

t_shell	*g_sh;

/*********************    FUNCTIONS    ************************/

// MAIN_C
char	*readline(const char *prompt);
void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

// INIT_C
void	init_shell(char **argv, char **env);
int		init_signals(void);

// INIT_UTILS_C
void	if_env_not_set(void);
void	create_sh_lvl(void);
void	init_shell_lvl(void);

// FREE_C
void	ft_free_env(void);
void	ft_free_global(void);
void	ft_exit(int status);
void	ft_free_cmd(void);

// ERROR_C
void	print_err(char *cmd, char *input, char *message, int exit_status);
void	print_perror(char *str1, char *str2, int exit_status);

void	lexer(char *str);
int		skip_quotes(char *str, int i);
int		get_next_pipe(char *str, int i);
char	**shell_split(char *str, char *sep, int s);
#endif
