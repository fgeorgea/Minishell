/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:11:45 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/17 14:06:55 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*********************      MACROS     ************************/

# define EXIT_PWD_FAILURE 12
# define EXIT_DUP_FAILURE 13
# define CD_RM "cd: error retrieving current directory: getcwd: cannot access\
 parent directories"

/*********************     FUNCTION    ************************/

// ECHO_C
void	echo_builtin(const char **strs);

// ENV_C
void	env_builtin(void);

// EXPORT_C
void	export_builtin(const char **strs);

// EXPORT_UTILS_C
void	sort_env_ascii(void);
void	print_export(void);
void	join_values_app(char *key, char *s1, char *s2);

// PWD_C
void	pwd_builtin(void);

// UNSET_C
void	unset_builtin(const char **vars);

// EXIT_C
void	exit_builtin(const char **arg);

// CD_C
void	cd_builtin(const char *str);

// CD_UTILS_C
void	ch_dir_str(char *dir, int *i, int *j);
void	add_oldpwd(char *current_dir, char *new_dir);
void	add_pwd(char *current_dir, char *new_dir);

// CALL_BUILTIN_C
int		is_builtin(const char *cmd);
void	exec_builtin(const char *cmd, const char **arg);

// REDIRECTIONS_BUILTINS_C
void	restore_stdout(int dup_stdout);
int		ft_dup(int fildes);
int		builtin_redirection(void);

#endif