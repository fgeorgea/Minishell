/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/19 14:08:05 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include "LIBFT/libft.h"
# include "includes/defines.h"
# include "includes/structs.h"
# include "includes/main.h"
# include "includes/pipex.h"
# include "includes/lexer.h"
# include "includes/builtins.h"
# include "includes/linked_lists.h"
# include "includes/sig.h"

t_shell	*g_sh;

#endif
