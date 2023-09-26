/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:38:37 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/26 15:03:14 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_buff
{
	char	buff[4096];
	int		buff_i;
	int		fd;
}t_buff;

int			ft_printf(int fd, const char *fmt, ...);
int			size_integer(unsigned int integer);
int			write_it(char c, va_list arg, t_buff *buff_struct);
int			write_hexa(char *base, unsigned int entiger, t_buff *buff_struct);
int			write_int(int i, t_buff *buff_struct);
int			write_str(char *str, t_buff *buff_struct);
int			write_char(char c, t_buff *buff_struct);
int			write_str_reverse(char *str, t_buff *buff_struct);
int			write_unsigned_int(unsigned int nb, t_buff *buff_struct);
int			write_addr(void *pointeur, char *base, t_buff *buff_struct);
int			ft_power(int a, int b);
void		ft_swap(char *str, int len_str);
char		*int_ft_itoa(int n);
char		*unsigned_ft_itoa(unsigned int n);
char		*ft_strdup(const char *s);
void		is_buff_full(t_buff *buff_struct);

#endif
