/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:55 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/02 15:16:55 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*********************      MACROS     ************************/

# define PIPE_ERR "An error occured on the pipe function\n"
# define WAITPID_ERR "An error occured on waitpid function\n"
# define DUP2_ERR "An error occured on dup2 function\n"
# define CLOSE_ERR "An error occured on close function\n"
# define FORK_ERR "An error occured on the fork function\n"
# define TMP_FILE "../.here_doc_tmp"
# define EXIT_OPEN_FAILURE 4
# define EXIT_CLOSE_FAILURE 5
# define EXIT_FORK_FAILURE 6
# define EXIT_PIPE_FAILURE 7
# define EXIT_DUP2_FAILURE 8
# define EXIT_WAITPID_FAILURE 9
# define EXIT_GNL_FAILURE 12
# define EXIT_EXECVE_FAILURE 13

/*********************      STRUCTS    ************************/

typedef struct s_pipex
{
	int		infile;
	int		here_doc;
	int		outfile;
	int		nbr_cmds;
	int		nbr_pipe;
	int		nbr_fork;
	int		nbr_paths;
	int		is_heredoc;
	int		exit_macro;
	char	*end_token;
	char	**paths;
	char	**env_array;
	int		**pipefd;
	pid_t	*pids;
}		t_pipex;

/*********************    FUNCTIONS    ************************/

// PIPEX.C
void	ft_pipex(void);

// INIT.C
void	ft_init_struct(void);

// INIT_UTILS_BONUS.C
void	ft_init_struct_vars(t_pipex *p);

// PARSING.C
void	check_cmd(char **cmd);
int		file_exist(char *str);

// FORK.C
void	ft_fork(int pos);
pid_t	*ft_createfork_array(t_pipex *p);
void	ft_first_child(t_pipex *p);
void	ft_last_child(int pos, t_pipex *p);
void	ft_middle_child(int pos, t_pipex *p);

// FORK_UTILS.C
void	ft_parent_close(int pos);
void	link_files(int fildes, int fildes2);

// EXEC.C
void	ft_exec(void);

// PIPE.C
void	ft_pipe(int pos);
int		**ft_createpipe_array(t_pipex *p);

// HERE_DOC.C
void	ft_here_doc(char *end_token);

// FREE.C
void	ft_free_array(char **tab);
void	ft_free_void_array(void **array, int len);
void	delete_tmp_file(void);
void	ft_free_pipex(void);

// PROTECTIONS.C
int		ft_tablen(char **tab);
void	ft_close(int *fd);
void	ft_dup2(int file1, int file2);
void	ft_waitpid(void);
int		ft_open(char *file, int flags, int perm);
void	ft_execve(const char *path, char *const argv[], char *const envp[]);

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