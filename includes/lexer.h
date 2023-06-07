/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:42:11 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/08 01:05:24 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	char	*word;
	int		token;
	int		quotes;
}			t_token;

// LEXER_C
void	lexer(char *str);

// LEXER_UTILS_C
int		skip_quotes(char *str, int i);
void	free_token(void *t);
void	display_syntax_err(void);
int		is_heredoc(t_list *last);
int		skip_trim(char *str, int *i);

// TOKENIZE_C
void	tokenize(t_list *head);

// TOKENIZE_UTILS_C
char	**shell_split_token(char *str, char *sep);

// SHELL_SPLIT_C
char	**shell_split(char *str, char *sep, int s);
int		is_in_sep(char c, char *sep);
char	**free_split(char **tab);

// REMOVE_QUOTES_C
void	trim_quotes(t_token *t, t_list *head);

// EXPANDER_C
void	expand(t_token *t, t_list *head);
int		insert_value(t_token *t, char *key, char *value, int *i);

// EXPANDER_UTILS_C
int		has_token(t_token *t);
char	*get_var_key(char *str, int *i, t_list *head);
int		has_variable(char *str);
int		has_quotes(char *str);
int		has_space(char *str);

// EXPAND_TRIM_SPLIT_C
t_list	*ex_trim_split(t_list *curr, t_token **t, t_list *head);

// JOIN_VALUE_SPLIT_C
int		join_value_split(char *value, t_list **curr, int *i, t_token **t);

// NEW_EXPANDER_C
void	expander(t_list **head, t_list *curr);
char	*get_key_value(char *key, int *i, t_list *head);

// POST_EXPANDER_C
t_list	*split_space(t_list *curr, t_list *head, t_token **t);

// REDIR_PARSER_C
t_list	*new_redir(t_list *curr, t_list **prev, t_list **head);

// PARSER_C
void	parser(t_list *head);
void	check_token_syntax(t_token *curr, t_token *next);

// ARG_PARSER_C
void	add_cmd_arg(t_list **head, int n, t_list *curr);

#endif
