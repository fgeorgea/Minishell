/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:55 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/26 19:41:40 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"
/**************************************************************/
/*********************      MACROS     ************************/
/**************************************************************/

# define PIPE_ERR "An error occured on the pipe function\n"
# define WAITPID_ERR "An error occured on waitpid function\n"
# define DUP2_ERR "An error occured on dup2 function\n"
# define CLOSE_ERR "An error occured on close function\n"
# define FORK_ERR "An error occured on the fork function\n"
# define TMP_FILE "/Users/fgeorgea/.here_doc_tmp"

/**************************************************************/
/*********************      STRUCTS    ************************/
/**************************************************************/

typedef struct s_pcmd
{
	char			**content;
	struct s_pcmd	*previous;
	struct s_pcmd	*next;
}		t_pcmd;

typedef struct s_pipex
{
	int		argc;
	int		nbr_cmds;
	int		nbr_pipe;
	int		nbr_fork;
	int		nbr_paths;
	int		infile;
	int		outfile;
	int		is_heredoc;
	char	*end_token;
	char	**paths;
	char	**env_array;
	int		**pipefd;
	pid_t	*pids;
}		t_pipex;

/**************************************************************/
/*********************    FUNCTIONS    ************************/
/**************************************************************/

// PIPEX.C
void	ft_pipex(int argc, char **argv);

// INIT.C
void	ft_init_struct(int argc, char **argv);

// INIT_UTILS_BONUS.C
void	ft_init_struct_vars(int argc, char **argv, t_pipex *p);
void	ft_check_here_doc(int argc, char **argv, t_pipex *p);

// ERROR.C
void	ft_error(const char *custom_perror, int does_exit);

// PARSING.C
void	ft_parse_cmds(void);

// CHAINED_LIST.C
void	ft_lstadd_back_pipex(t_pcmd **lst, t_pcmd *new);
t_pcmd	*ft_lstlast_pipex(t_pcmd *lst);
void	ft_lstclear_pipex(t_pcmd **lst);
t_pcmd	*ft_lstnew_pipex(char **content, t_pcmd *previous);
void	ft_set_lst_head(t_pcmd **lst);

// FORK.C
void	ft_fork(int pos);
pid_t	*ft_createfork_array(t_pipex *p);
void	ft_first_child(t_cmd *cmd, t_pipex *p);
void	ft_last_child(int pos, t_cmd *cmd, t_pipex *p);
void	ft_middle_child(int pos, t_cmd *cmd, t_pipex *p);

// FORK_UTILS.C
void	ft_parent_close(int pos);

// EXEC.C
void	ft_exec(void);

// PIPE.C
void	ft_pipe(int pos);
int		**ft_createpipe_array(t_pipex *p);

// HERE_DOC.C
void	ft_here_doc(void);

// FREE.C
void	ft_free_int_array(int **array, int len);
void	ft_free_array(char **tab);
void	ft_unlink_tmp(void);

// UTILS.C
int		ft_tablen(char **tab);
void	ft_close(int *fd);
void	ft_dup2(int file1, int file2);
void	ft_waitpid(void);

#endif