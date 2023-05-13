/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:55 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 16:30:57 by fgeorgea         ###   ########.fr       */
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

# define IN_FLAGS O_RDONLY
# define HEREDOC_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
# define OUT_FLAGS (O_WRONLY | O_TRUNC | O_CREAT)
# define OUT_APP_FLAGS (O_WRONLY | O_APPEND | O_CREAT)

/*********************      STRUCTS    ************************/

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	size_t	nbr_cmds;
	size_t	nbr_pipe;
	size_t	nbr_fork;
	size_t	nbr_paths;
	char	**paths;
	char	**env_array;
	int		**pipefd;
	pid_t	*pids;
}		t_pipex;

/*********************    FUNCTIONS    ************************/

// PIPEX.C
void	ft_pipex(void);

// INIT.C
void	init_struct_pipex(void);

// PARSING.C
int		found_cmd(char **cmd);
int		file_exist(const char *str);

// FORK.C
void	ft_fork(size_t pos);
pid_t	*create_fork_array(const t_pipex *p);
void	first_child(const t_pipex *p);
void	last_child(size_t pos, const t_pipex *p);
void	middle_child(size_t pos, const t_pipex *p);

// FORK_UTILS.C
void	link_files(int fildes, int fildes2);

// EXEC.C
void	exec_cmds(void);

// EXEC_UTILS.C
void	check_cmd(char **cmd);
void	update_last_cmd(const char **cmd);

// PIPE.C
void	ft_pipe(size_t pos);
int		**create_pipe_array(const t_pipex *p);

// CLOSE_PIPES.C
void	close_pipes_children(size_t pos, t_pipex *p);
void	close_pipes_parent(size_t pos, t_pipex *p);

// HERE_DOC.C
void	here_doc(char *end_token);

// FREE.C
void	ft_free_array(char **array);
void	ft_free_array_pos(void **array, int pos);
void	delete_tmp_file(void);
void	free_pipex(void);
void	ft_free(void *ptr);

// PROTECTIONS.C
void	ft_close(int *fd);
void	ft_dup2(int file1, int file2);
void	ft_waitpid(void);
int		ft_open(char *file, int flags, int perm);
void	ft_execve(char *const *argv, char *const *envp);

// ENV.C
void	lst_to_array(t_env **lst);
char	*get_env_value(const char *key);
t_env	*get_env_struct(const char *needle);
void	change_env_value(const char *key, const char *new_value);

// REDIR.C
int		open_outfile(t_cmd *cmd);
int		open_infile(t_cmd *cmd);

// UTILS.C
size_t	arraylen(const char **array);
int		compare_keys(const char *key, const char *needle);

#endif