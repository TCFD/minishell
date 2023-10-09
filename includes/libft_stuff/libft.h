/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:39:15 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/09 16:02:24 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef LINES
#  define LINES 1
# endif

typedef struct s_list
{
	char			*content;
	char			type;
	struct s_list	*next;
}	t_list;

long long int		ft_atoi(const char *nptr);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_lstsize(t_list *lst);
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t nmeb, size_t size);
char				*ft_itoa(long long int n);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_strnstr(const char *big, \
						const char *little, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
t_list				*ft_lstnew(char *content, char type);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
						void (*del)(void *));
int					ft_len(char *str);
int					null_cara_found(char *static_buff);
void				new_buff_static(char **static_buff, int idx_null_cara);
char				*output_result(char **static_buff, int idx_null_cara);
char				*get_next_line(int fd);
char				*main_code(int fd);
char				*malloc_fill(char *content);
char				*ft_cpy(const char *what_to_cpy, int possible_to_free);
char				*read_fd(int fd, int *verification, char **static_buff);
char				*ft_join(char *s1, char *s2);
char				*ft_strchr_rc(const char *s, int c);

#endif
