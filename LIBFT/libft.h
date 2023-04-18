/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 10:22:27 by dpeyrat           #+#    #+#             */
/*   Updated: 2023/02/07 12:38:24 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

# define BUFFER_SIZE 256

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_conv
{
	char	c;
	char	s;
	char	h;
	char	min;
	int		min_v;
	char	max;
	int		max_v;

	int		i;
	int		count;

	va_list	ap;
}		t_conv;

int				ft_atoi(const char *str);
void			ft_bzero(void *var, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, void const *src, size_t len);
void			*ft_memset(void *str, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *str, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *str, int fd);
char			**ft_split(char const *str, char c);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t n);
size_t			ft_strlcpy(char *dest, const char *src, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strmapi(char const *str, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t size);
char			*ft_strnstr(const char *str, const char *find, size_t n);
char			*ft_strrchr(const char *str, int c);
char			*ft_strtrim(char const *str, char const *set);
char			*ft_substr(char const *str, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *));
int				ft_lstsize(t_list *lst);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

int				convert_str(t_conv *conv, char *str);
int				convert_percent(t_conv *conv);
int				convert_char(t_conv *conv, int n);
int				convert_uint(t_conv *conv, unsigned int n);
int				convert_int(t_conv *conv, int n);
int				convert_addr(t_conv *conv, unsigned long long n);
int				ft_intulen(unsigned int n, unsigned int len);
int				ft_putunbr_base(unsigned int n, char *base, unsigned int len);
unsigned int	ft_abs(int n);
int				ft_writexchar(int n, char c);
void			get_conv(const char *str, int *i, t_conv *conv);
int				ft_iscontained(char *str, char c);
int				ft_printf(const char *str, ...);
char			*get_next_line(int fd);
char			*ft_strndup(char *str, int n);

#endif
