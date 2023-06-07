/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:11:45 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/08 00:26:19 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// ECHO_C
void	echo_builtin(const char **strs);

// ENV_C
void	env_builtin(const char **arg);

// EXPORT_C
void	export_builtin(const char **strs);
void	add_var_to_env(const char *str, size_t pos);
int		check_valid_key(const char *str);

// EXPORT_UTILS_C
void	sort_env_ascii(void);
void	print_export(void);
void	join_values_app(char *key, char *s1, char *s2);
void	add_var_to_env_null(const char *key);

// PWD_C
void	pwd_builtin(void);

// UNSET_C
void	unset_builtin(const char **vars);

// EXIT_C
void	exit_builtin(const char **arg);

// EXIT_UTILS_C
void	skip_white_space(char **arg);
void	exit_non_numeric_arg(const char *str);

// CD_C
void	cd_builtin(const char *str);

// CD_UTILS_C
void	ch_dir_str(char *dir, int *i, int *j);
void	add_oldpwd(char *current_dir, char *new_dir);
void	add_pwd(char *current_dir, char *new_dir);
int		test_access(char *str);
int		cd_crash_handler(const char *dir);
char	*get_cd_special_dir(const char *str);

// CALL_BUILTIN_C
int		is_builtin(const char *cmd);
void	exec_builtin(const char *cmd, const char **arg);

// REDIRECTIONS_BUILTINS_C
int		builtin_redirection(void);

// RESTORE_STDOUT_C
void	restore_stdout(int dup_stdout);
int		ft_dup(int fildes);

#endif