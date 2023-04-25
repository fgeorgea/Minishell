/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/25 14:28:39 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include "LIBFT/libft.h"
# include "exec/pipex.h"

# define EXIT_MALLOC_FAILURE 2

# define OUT 0
# define OUT_APP 1
# define IN 2
# define HEREDOC 3

/**************************************************************/
/*********************      STRUCTS    ************************/
/**************************************************************/

typedef struct s_redir
{
	char			*key;
	int				mode;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*redir;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_shell
{
	char	*name;

	t_cmd	*cmd;
	char	*str;
	t_env	*env;

	t_pipex	*pipex;
}			t_shell;

t_shell	*g_sh;

/**************************************************************/
/*********************    FUNCTIONS    ************************/
/**************************************************************/

char	*readline(const char *prompt);
void	rl_replace_line(const char *text, int clear_undo);
void	init_shell(char **argv, char **env);
int		init_signals(void);
void	ft_free_env(void);
void	ft_free_global(void);
void	ft_exit(int status);
#endif
