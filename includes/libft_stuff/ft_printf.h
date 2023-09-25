/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:38:37 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/24 21:05:36 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int			ft_printf(int fd, const char *fmt, ...);
int			size_integer(unsigned int integer);
int			write_it(char c, va_list arg, int fd);
int			write_hexa(char *base, unsigned int entiger, int fd);
int			write_int(int i, int fd);
int			write_str(char *str, int fd);
int			write_char(char c, int fd);
int			write_str_reverse(char *str, int fd);
int			write_unsigned_int(unsigned int nb, int fd);
int			write_addr(void *pointeur, char *base, int fd);
int			ft_power(int a, int b);
void		ft_swap(char *str, int len_str);
char		*int_ft_itoa(int n);
char		*unsigned_ft_itoa(unsigned int n);
char		*ft_strdup(const char *s);

#endif
