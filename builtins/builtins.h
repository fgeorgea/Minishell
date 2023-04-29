/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:11:45 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 01:34:48 by fgeorgea         ###   ########.fr       */
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
void	ft_export(void);

// PWD.C
char	*ft_pwd(void);

#endif