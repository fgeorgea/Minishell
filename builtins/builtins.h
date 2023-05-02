/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:11:45 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/02 15:30:29 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*********************      MACROS     ************************/

# define EXIT_PWD_FAILURE 10
# define EXIT_CHDIR_FAILURE 11

/*********************     FUNCTION    ************************/

// ECHO.C
void	ft_echo(char **strs);

// ENV.C
void	ft_env(void);

// EXPORT.C
void	ft_export(char *str);

// PWD.C
char	*ft_pwd(void);

// UNSET.C
void	ft_unset(char **vars);

#endif