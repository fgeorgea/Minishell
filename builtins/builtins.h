/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:11:45 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 16:49:48 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*********************      MACROS     ************************/

# define EXIT_PWD_FAILURE 10

/*********************     FUNCTION    ************************/

// ECHO.C
void	echo_builtin(const char **strs);

// ENV.C
void	env_builtin(void);

// EXPORT.C
void	export_builtin(const char **strs);

// EXPORT_UTILS.C
void	sort_env_ascii(void);
void	print_export(void);

// PWD.C
void	pwd_builtin(void);

// UNSET.C
void	unset_builtin(const char **vars);

// EXIT.C
void	exit_builtin(const char **arg);

// CD.C
void	cd_builtin(const char *str);

// CALL_BUILTIN.C
int		is_builtin(const char *cmd);
void	exec_builtin(const char *cmd, const char **arg);


void	print_array(char **array); // GET RID OF SHAT SHIT !!!

#endif