/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:13:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/08 00:14:14 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// MAIN_C
char	*readline(const char *prompt);
void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);

// ENV_C
void	init_env(char **env);
void	init_oldpwd(void);
void	if_env_not_set(void);
void	create_sh_lvl(void);
void	init_shell_lvl(void);

// PROMPT_C
void	ft_add_history(void);
void	create_config_str(void);
void	create_prompt(void);

// ALIAS_C
void	init_aliases(void);

// INIT_C
void	ft_readline(void);
void	init_shell(char **argv, char **env);
int		init_signals(void);

// INIT_UTILS_C
void	if_env_not_set(void);
void	create_sh_lvl(void);
void	init_shell_lvl(void);
void	print_welcome_message(void);

// FREE_C
void	ft_free_env(void);
void	ft_free_global(void);
void	ft_exit(int status);
void	ft_free_cmd(void);
void	free_readline(void);

// ERROR_C
void	print_err(char *cmd, char *input, char *message, int exit_status);
void	print_perror(char *str1, char *str2, int exit_status);

#endif