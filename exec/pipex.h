/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:55 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:10:38 by fgeorgea         ###   ########.fr       */
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
	int		**pipefd;
	pid_t	*pids;
	t_pcmd	*lst;
}		t_pipex;

/**************************************************************/
/*********************    FUNCTIONS    ************************/
/**************************************************************/

// INIT.C
void	ft_init_struct(int argc, char **argv, t_pipex *p);

// ERROR.C
void	ft_error(t_pipex *p, const char *custom_perror, int does_exit);

// PARSING.C
void	ft_parse_cmds(t_pipex *p);

// CHAINED_LIST.C
void	ft_lstadd_back_pipex(t_pcmd **lst, t_pcmd *new);
t_pcmd	*ft_lstlast_pipex(t_pcmd *lst);
void	ft_lstclear_pipex(t_pcmd **lst);
t_pcmd	*ft_lstnew_pipex(char **content, t_pcmd *previous, t_pipex *p);
void	ft_set_lst_head(t_pcmd **lst);

// UTILS.C
int		ft_tablen(char **tab, t_pipex *p);
void	ft_close(int *fd, t_pipex *p);
void	ft_dup2(int file1, int file2, t_pipex *p);
void	ft_waitpid(t_pipex *p);

// FORK.C
void	ft_fork(int pos, t_pipex *p);
pid_t	*ft_createfork_array(t_pipex *p);
void	ft_first_child(char **env, t_pipex *p);
void	ft_last_child(int pos, char **env, t_pipex *p);
void	ft_middle_child(int pos, char **env, t_pipex *p);

// EXEC.C
void	ft_exec(char **env, t_pipex *p);

// PIPE.C
void	ft_pipe(int pos, t_pipex *p);
int		**ft_createpipe_array(t_pipex *p);

// FORK_UTILS.C
void	ft_parent_close(int pos, t_pipex *p);

// INIT_UTILS_BONUS.C
void	ft_init_struct_vars(int argc, char **argv, t_pipex *p);
void	ft_check_here_doc(int argc, char **argv, t_pipex *p);

// HERE_DOC_BONUS.C
void	ft_here_doc(t_pipex *p);

// FREE_BONUS.C
void	ft_free_int_array(int **array, int len);
void	ft_free_array(char **tab);
void	ft_unlink_tmp(void);

#endif