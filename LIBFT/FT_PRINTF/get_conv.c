/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:41:30 by dopeyrat          #+#    #+#             */
/*   Updated: 2022/10/25 12:03:33 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	get_min_field(const char *str, int n)
{
	int	i;

	i = 0;
	while (i < n && str[i] != '.' && (!ft_isdigit(str[i]) || str[i] == '0'))
		i++;
	if (i >= n || str[i] == '.')
		return (0);
	return (ft_atoi(&str[i]));
}

void	get_min_zero(const char *str, char *min, int n)
{
	int	i;

	i = 0;
	while (i < n && str[i] != '.')
	{
		if (str[i] == '0')
		{
			*min = '0';
			return ;
		}
		if (ft_isdigit(str[i]))
		{
			while (ft_isdigit(str[i]))
				i++;
		}
		i++;
	}
}

void	get_mflag(const char *str, int *i, t_conv *conv, int j)
{
	conv->c = str[*i];
	(*i)++;
	conv->min_v = get_min_field(&str[j], (*i) - j);
	if (conv->min_v && !conv->min)
		conv->min = 1;
	if (conv->min != '-')
		get_min_zero(&str[j], &conv->min, (*i) - j);
}

void	get_conv(const char *str, int *i, t_conv *conv)
{
	int	j;

	j = *i;
	while (ft_iscontained("-0123456789 +#", str[*i]))
	{
		if (str[*i] == '-')
			conv->min = '-';
		else if (str[*i] == ' ' && conv->s != '+')
			conv->s = ' ';
		else if (str[*i] == '+')
			conv->s = '+';
		else if (str[*i] == '#')
			conv->h = 1;
		(*i)++;
	}
	if (str[*i] == '.')
	{
		conv->max = 1;
		(*i)++;
		conv->max_v = ft_atoi(&str[*i]);
		while (ft_isdigit(str[*i]))
			(*i)++;
	}
	get_mflag(str, i, conv, j);
}
