/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:28:46 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/05 15:08:04 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	*ft_strdup_free(const char *str);
char	*ft_strjoin_free(char const *s1, char const *s2);
char	**ft_split_exit(char const *str, char c);

#endif