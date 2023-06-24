/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_lib.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:06:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/25 01:24:47 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_LIB_H
# define STRUCTS_LIB_H

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
	int				nbr;
}		t_list;

typedef struct s_char
{
	struct s_char	*next;
	char			c;
}		t_char;

typedef struct s_generic
{
	struct s_generic	*next;
}		t_generic;

#endif
