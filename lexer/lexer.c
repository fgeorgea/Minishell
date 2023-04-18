/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:16:09 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/03/31 15:16:11 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_tokens(t_cmd *cmd, char *str, int n)//, t_shell *sh)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && i < n)
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i, n);
		i++;
	}
	cmd->cmd = ft_strndup(str, i);
	/*if (!cmd->cmd)
		ft_exit(sh, EXIT_MALLOC_FAILURE);*/
	while (i < n)
	{
		while ()
	}
}

void	set_cmds(t_shell *sh, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		j = get_next_pipe(&str[i]);
		sh->cmd[k].r_c = count_redir(&str[i], j - i);
		sh->cmd[k].redir = ft_calloc(sizeof(t_redir), sh->cmd[k].r_c + 1);
		/*if (!sh->cmd[k].redir)
			ft_exit(sh, EXIT_MALLOC_FAILURE);*/
		sh->cmd[k].redir[sh->cmd[k].r_c] = NULL;
		get_tokens(&sh->cmd[k], &str[i], j - i);
		i = j;
		if (str[i] == '|')
			i++;
		k++;
	}
}

void	lexer(t_shell *sh, char *str)
{
	if (sh->cmd)
		ft_free_cmd(sh->cmd, sh->c_count);
	sh->c_count = count_cmds(str) + 1;
	sh->cmd	= ft_calloc(sizeof(t_cmd *), sh->c_count + 1);
	/*if (!sh->cmd)
		ft_exit(sh, EXIT_MALLOC_FAILURE);*/
	sh->cmd[sh->c_count] = NULL;
	set_cmds(sh, str);
}
