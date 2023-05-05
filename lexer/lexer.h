/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:42:11 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/04 19:39:26 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define NO_S_ERR 0
# define S_ERR_NL 1
# define S_ERR_OUT 2
# define S_ERR_IN 3
# define S_ERR_APP 4
# define S_ERR_HERE 5
# define S_ERR_RW 6
# define S_ERR_PIPE 7

typedef struct s_token
{
	char	*word;
	int		token;
	int		quotes;
}			t_token;

void	tokenize(t_list *head);
int		is_in_sep(char c, char *sep);
char	**free_split(char **tab);
void	expander(t_list *head);
void	post_expander(t_list *head);
void	free_token(void *t);
void	remove_quotes(t_list *head);
void	display_syntax_err(void);
void	parser(t_list *head);
int		has_variable(char *str);
int		has_quotes(char *str);

#endif
