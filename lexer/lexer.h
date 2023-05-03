/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:42:11 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/27 17:42:28 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	char	*word;
	int		token;
}			t_token;

void	tokenize(t_list *head);
int		is_in_sep(char c, char *sep);
char	**free_split(char **tab);
void	expander(t_list *head);
void	post_expander(t_list *head);
void	free_token(void *t);
void	remove_quotes(t_list *head);

#endif
