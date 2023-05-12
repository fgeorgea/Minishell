/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:31:22 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/12 12:15:04 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LISTS_H
# define LINKED_LISTS_H

// LINKED_LIST_ENV.C
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *value);
int		lstsize_env(t_env **lst);
void	del_one_env(t_env *env);

// LINKED_LIST_CMD.C
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew_cmd(char **cmd, t_redir *redir);
int		lstsize_cmd(void);

// LINKED_LIST_REDIR.C

#endif