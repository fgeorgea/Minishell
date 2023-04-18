/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/03/15 12:37:15 by dopeyrat         ###   ########.fr       */
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

# define EXIT_SUCESS 0
# define EXIT_FAILURE 1
# define EXIT_MALLOC_FAILURE 2

# define OUT 0
# define OUT_APP 1
# define IN 2
# define HEREDOC 3

typedef struct	s_redir
{
	char			*key;
	int				mode;
	struct s_redir	*next;
}			t_redir;

typedef struct	s_cmd
{
	char			**cmd;
	t_redir			*redir;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_shell
{
	t_cmd	*cmd;
	char	*str;
}			t_shell;

char	*readline(const char *prompt);
void 	rl_replace_line (const char *text, int clear_undo);

#endif
