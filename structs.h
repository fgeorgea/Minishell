/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:08:00 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/02 15:20:49 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

# include "exec/pipex.h"

typedef struct s_shell
{
	char	*name;
	int		pipe_exit;
	char	*str;

	t_cmd	*cmd;
	t_env	*env;
	t_pipex	*pipex;
}			t_shell;

#endif 