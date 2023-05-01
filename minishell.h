/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/02 00:52:23 by fgeorgea         ###   ########.fr       */
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
# include "LIBFT/libft.h"
# include "exec/pipex.h"
# include "lexer/lexer.h"
# include "builtins/builtins.h"
# include "utils/utils.h"

/*********************    MACROS       ************************/

# define EXIT_MALLOC_FAILURE 2
# define EXIT_SIGNAL_FAILURE 3

// PIPE MODE
# define OUT 0
# define OUT_APP 1
# define IN 2
# define HEREDOC 3

/*********************      STRUCTS    ************************/

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
	char	*str;

	t_cmd	*cmd;
	t_env	*env;

	t_pipex	*pipex;
}			t_shell;

t_shell	*g_sh;

/*********************    FUNCTIONS    ************************/

char	*readline(const char *prompt);
void	rl_replace_line(const char *text, int clear_undo);
void	init_shell(char **argv, char **env);
int		init_signals(void);
void	ft_free_env(void);
void	ft_free_global(void);
void	ft_exit(int status);
void	lexer(char *str);
int		skip_quotes(char *str, int i);
int		get_next_pipe(char *str, int i);
char	**shell_split(char *str, char *sep);
void	ft_free_cmd(void);

/*********************    PIPEX        ************************/

// ENV.C
int		lstsize_env(t_env **lst);
int		lstsize_cmd(void);
char	**lst_to_array(t_env **lst);
char	*get_env_value(char *key, int size);

// REDIR.C
t_redir	*get_out_redir(t_redir **redirection);
t_redir	*get_in_redir(t_redir **redirection);
int		open_outfile(t_cmd *cmd);
int		open_infile(t_cmd *cmd);

// DEBUG.C
void    fill_linked_lists();

#endif
