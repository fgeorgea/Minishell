/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:03 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 12:02:47 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *str)
{
	int	tmp_fd;

	tmp_fd = open(str, O_WRONLY);
	if (tmp_fd == -1 && errno == EISDIR)
		return (1);
	ft_close(&tmp_fd);
	return (0);
}
