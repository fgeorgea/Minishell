/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:22:52 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/08 00:28:27 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

// EXEC CRASH CODES
# define EXIT_MALLOC_FAILURE 2
# define EXIT_SIGNAL_FAILURE 3
# define EXIT_OPEN_FAILURE 4
# define EXIT_CLOSE_FAILURE 5
# define EXIT_PIPE_FAILURE 6
# define EXIT_DUP2_FAILURE 7
# define EXIT_WAITPID_FAILURE 8
# define EXIT_EXECVE_FAILURE 9
# define EXIT_CTRL_D 10
# define EXIT_PWD_FAILURE 11
# define EXIT_DUP_FAILURE 12

// SYNTHAX ERRORS
# define NO_S_ERR 0
# define S_ERR_NL 1
# define S_ERR_OUT 2
# define S_ERR_IN 3
# define S_ERR_APP 4
# define S_ERR_HERE 5
# define S_ERR_RW 6
# define S_ERR_PIPE 7
# define S_ERR_TRIPLE 8

// PIPE MODE
# define OUT 0
# define OUT_APP 1
# define IN 2
# define HEREDOC 3
# define HEREDOC_EXP 4

// SIGNALS
# define DEFAULT 0
# define SIG_HERE 1
# define PARENT 2
# define CHILD 3

// EXEC CRASH MESSAGES
# define NSFOD ": No such file or directory"
# define CNF ": command not found"
# define PIPE_ERR "An error occured on the pipe function\n"
# define WAITPID_ERR "An error occured on waitpid function\n"
# define DUP2_ERR "An error occured on dup2 function\n"
# define CLOSE_ERR "An error occured on close function\n"
# define FORK_ERR "An error occured on the fork function\n"
# define CD_RM "cd: error retrieving current directory: getcwd: cannot access\
 parent directories"
# define NAVI "': not a valid identifier"

#endif