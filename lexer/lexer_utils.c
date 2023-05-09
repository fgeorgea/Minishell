/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:53:59 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/04 19:41:13 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_quotes(char *str, int i)
{
	int	j;

	j = i + 1;
	if (str[i] == '"')
	{
		while (str[j] && str[j] != '"')
			j++;
		if (str[j] == '"')
			return (j);
	}
	else if (str[i] == '\'')
	{
		while (str[j] && str[j] != '\'')
			j++;
		if (str[j] == '\'')
			return (j);
	}
	return (i);
}

void	free_token(void *t)
{
	t_token	*token;

	token = t;
	free(token->word);
	free(token);
}

void	display_syntax_err(void)
{
	ft_putstr_fd(g_sh->name, 2);
	if (g_sh->s_err == S_ERR_NL)
		ft_putstr_fd(": syntax error near unexpected token `newline'\n", 2);
	else if (g_sh->s_err == S_ERR_IN)
		ft_putstr_fd(": syntax error near unexpected token `<'\n", 2);
	else if (g_sh->s_err == S_ERR_OUT)
		ft_putstr_fd(": syntax error near unexpected token `>'\n", 2);
	else if (g_sh->s_err == S_ERR_APP)
		ft_putstr_fd(": syntax error near unexpected token `>>'\n", 2);
	else if (g_sh->s_err == S_ERR_HERE)
		ft_putstr_fd(": syntax error near unexpected token `<<'\n", 2);
	else if (g_sh->s_err == S_ERR_RW)
		ft_putstr_fd(": syntax error near unexpected token `<>'\n", 2);
	else if (g_sh->s_err == S_ERR_PIPE)
		ft_putstr_fd(": syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd(": unknown syntax error\n", 2);
}

int	has_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = skip_quotes(str, i);
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_iswhitespace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_heredoc(t_list *last)
{
	t_token	*content;

	if (!last)
		return (0);
	content = last->content;
	if (!content->token)
		return (0);
	if (content->word[0] == '<' && content->word[1] == '<')
		return (1);
	return (0);
}

int	skip_trim(char *str, int *i)
{
	int	j;

	if (i[5] == i[0])
		return (i[0]);
	j = i[5];
	while (str[j])
	{
		str[j] = str[j + 1];
		j++;
	}
	j = i[0] - 1;
	while (str[j])
	{
		str[j] = str[j + 1];
		j++;
	}
	return (i[0] - 2);
}