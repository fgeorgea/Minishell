/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:28:46 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 01:53:52 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	*ft_strdup_exit(const char *str);
char	*ft_strjoin_exit(char const *s1, char const *s2);
char	**ft_split_exit(char const *str, char c);

#endif