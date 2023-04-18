/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:31:36 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/02/07 12:32:52 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dst;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	if (i > n)
		i = n;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	*nl_found(char **leftover, int i)
{
	char	*temp;
	char	*new_left;

	temp = ft_strndup(*leftover, i + 1);
	if (!temp)
		return (0);
	new_left = ft_strdup(&(*leftover)[i + 1]);
	if (!new_left)
	{
		free(temp);
		return (0);
	}
	free(*leftover);
	*leftover = new_left;
	return (temp);
}

char	*end_file(char **leftover)
{
	char	*temp;

	if (!*leftover)
		return (0);
	temp = *leftover;
	*leftover = 0;
	if (!temp[0])
	{
		free(temp);
		return (0);
	}
	return (temp);
}

int	ft_read(char **leftover, int fd)
{
	int		ret;
	char	buff[BUFFER_SIZE + 1];
	char	*old_left;

	ret = read(fd, buff, BUFFER_SIZE);
	if (ret == -1)
		return (0);
	buff[ret] = 0;
	old_left = *leftover;
	*leftover = ft_strjoin(old_left, buff);
	if (!(*leftover))
	{
		*leftover = old_left;
		return (0);
	}
	free(old_left);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*leftover[OPEN_MAX];
	int			ret;
	int			i;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (0);
	if (!leftover[fd])
		leftover[fd] = ft_strdup("");
	if (!leftover[fd])
		return (0);
	ret = BUFFER_SIZE;
	while (1)
	{
		i = -1;
		while (leftover[fd] && leftover[fd][++i])
		{
			if (leftover[fd][i] == '\n')
				return (nl_found(&leftover[fd], i));
		}
		if (ret != BUFFER_SIZE)
			return (end_file(&leftover[fd]));
		else
			ret = ft_read(&leftover[fd], fd);
	}
	return (0);
}
