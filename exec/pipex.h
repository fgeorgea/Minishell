/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:55 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 15:22:46 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_pipex
{
	char			**content;
	struct s_pipex	*previous;
	struct s_pipex	*next;
}		t_pipex;

typedef struct s_global
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
	int		**pipefd;
	pid_t	*pids;
	t_pipex	*lst;
}		t_global;

/**************************************************************/
/*********************    FUNCTIONS    ************************/
/**************************************************************/

// INIT.C
void	ft_init_struct(int argc, char **argv, char **end, t_global *g);

// ERROR.C
void	ft_error(t_global *g, const char *custom_perror);

// PARSING.C
void	ft_parse_cmds(t_global *g);

// CHAINED_LIST.C
void	ft_lstadd_back_pipex(t_pipex **lst, t_pipex *new);
t_pipex	*ft_lstlast_pipex(t_pipex *lst);
void	ft_lstclear_pipex(t_pipex **lst);
t_pipex	*ft_lstnew_pipex(char **content, t_pipex *previous, t_global *g);
void	ft_set_lst_head(t_pipex **lst);

// UTILS.C
int		ft_tablen(char **tab, t_global *g);
void	ft_close(int *fd, t_global *g);
void	ft_dup2(int file1, int file2, t_global *g);
void	ft_waitpid(t_global *g);

// FORK.C
void	ft_fork(int pos, t_global *g);
pid_t	*ft_createfork_array(t_global *g);
void	ft_first_child(char **env, t_global *g);
void	ft_last_child(int pos, char **env, t_global *g);
void	ft_middle_child(int pos, char **env, t_global *g);

// EXEC.C
void	ft_exec(char **env, t_global *g);

// PIPE.C
void	ft_pipe(int pos, t_global *g);
int		**ft_createpipe_array(t_global *g);

// FORK_UTILS.C
void	ft_parent_close(int pos, t_global *g);

// INIT_UTILS_BONUS.C
void	ft_init_struct_vars(int argc, char **argv, t_global *g);
void	ft_check_here_doc(int argc, char **argv, t_global *g);

// HERE_DOC_BONUS.C
void	ft_here_doc(t_global *g);

// FREE_BONUS.C
void	ft_free_int_array(int **array, int len);
void	ft_free_array(char **tab);
void	ft_unlink_tmp(void);

#endif