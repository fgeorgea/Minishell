/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:08:00 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 18:33:55 by fgeorgea         ###   ########.fr       */
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
}		t_env;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		is_in_child;
	int		dup_stdin;
	char	*hd_tmp;
	size_t	nbr_cmds;
	size_t	nbr_pipe;
	size_t	nbr_fork;
	size_t	nbr_paths;
	char	**paths;
	char	**env_array;
	int		**pipefd;
	pid_t	*pids;
}		t_pipex;

typedef struct s_shell
{
	char	*name;
	int		pipe_exit;
	int		is_exit_lst_cmd;
	int		here_doc_status;
	int		is_child;
	char	*str;

	int		s_err;

	t_cmd	*cmd;
	t_env	*env;
	t_pipex	*pipex;
}			t_shell;

#endif
