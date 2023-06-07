/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:55 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 11:57:12 by fgeorgea         ###   ########.fr       */
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
# define EXIT_OPEN_FAILURE 4
# define EXIT_CLOSE_FAILURE 5
# define EXIT_PIPE_FAILURE 6
# define EXIT_DUP2_FAILURE 7
# define EXIT_WAITPID_FAILURE 8
# define EXIT_EXECVE_FAILURE 9
# define NSFOD ": No such file or directory"
# define CNF ": command not found"

/*********************    FUNCTIONS    ************************/

// PIPEX_C
void	ft_pipex(void);

// INIT_C
void	init_struct_pipex(void);

// PARSE_CMD_C
int		found_cmd(char **cmd);
int		file_exist(const char *str);
int		does_cmd_exist(const char *str);
int		try_cat_path_cmd(char **cmd, size_t pos);

// PARSE_CMD_UTILS_C
int		is_relative_path(const char *cmd);
void	try_catch_cmd(char **cmd);

// FORK_C
int		ft_fork(size_t pos);
pid_t	*create_fork_array(const t_pipex *p);
void	first_child(const t_pipex *p);
void	last_child(size_t pos, const t_pipex *p);
void	middle_child(size_t pos, const t_pipex *p);

// FORK_UTILS_C
void	ft_dup2(int file1, int file2);
void	link_files(int fildes, int fildes2);

// EXEC_C
void	exec_cmds(t_pipex *p, t_cmd *cmd);
void	ft_execve(char *const *argv, char *const *envp);

// EXEC_UTILS_C
void	check_cmd(char **cmd);
void	update_last_cmd(const char **cmd);
int		is_single_builtin(void);

// PIPE_C
void	ft_pipe(size_t pos);
int		**create_pipe_array(const t_pipex *p);
void	close_all_pipes(void);

// CLOSE_PIPES_C
void	close_pipes_children(size_t pos, t_pipex *p);
void	close_pipes_parent(size_t pos, t_pipex *p);

// HERE_DOC_C
void	here_doc(char *end_token);
void	ft_here_doc_exp(char *end_token);

// EXPAND_HERE_DOC_C
void	expand_heredoc(char **str);

// FREE_C
void	ft_free_array(char **array);
void	ft_free_array_pos(void **array, int pos);
void	delete_tmp_file(char *file);
void	free_pipex(void);
void	ft_free(void **ptr);

// PROTECTIONS_C
void	ft_close(int *fd);
int		ft_open(char *file, int flags, int perm);
int		ft_open_redir(char *file, int mode, int perm);

// WAIT_C
void	ft_waitpid(void);

// ENV_C
void	lst_to_array(t_env **lst);
char	*get_env_value(const char *key);
t_env	*get_env_struct(const char *needle);
void	change_env_value(const char *key, const char *new_value);

// REDIR_C
int		test_redir_open(char *file, int mode, int perm);
void	setup_redir(t_redir *redirection, t_pipex *p);
void	setup_heredoc(t_redir *redirection, int pos);

// REDIR_UTILS_C
int		is_out_redir(int redir_mode);
void	restore_stdin(int dup_stdin);
void	create_hd_name(int pos);
void	unlink_all_tmp(void);

// UTILS_C
size_t	arraylen(const char **array);
int		compare_keys(const char *key, const char *needle);
void	exit_only_child(int exit_code);
void	set_exit(int exit_code);
void	set_lst_cmd(int pos);

// CMD_UTILS_C
int		is_directory(const char *str);

// UNDERSCORE_UTILS_C
int		try_cat_path_cmd_underscore(char **cmd, size_t pos);

#endif
