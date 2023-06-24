/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_lib.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:06:03 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/25 01:24:31 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_LIB_H
# define MEMORY_LIB_H

void	ft_free(void **ptr);
void	ft_var_free(int len, ...);
void	*ft_realloc(void *ptr, size_t size);

#endif
