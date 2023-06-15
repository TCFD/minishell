/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:38:37 by tboldrin          #+#    #+#             */
/*   Updated: 2022/12/16 15:42:32 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int			ft_printf(const char *fmt, ...);
int			size_integer(unsigned int integer);
int			write_it(char c, va_list arg);
int			write_hexa(char *base, unsigned int entiger);
int			write_int(int i);
int			write_str(char *str);
int			write_char(char c);
int			write_str_reverse(char *str);
int			write_unsigned_int(unsigned int nb);
int			write_addr(void *pointeur, char *base);
int			ft_power(int a, int b);
void		ft_swap(char *str, int len_str);
char		*int_ft_itoa(int n);
char		*unsigned_ft_itoa(unsigned int n);
char		*ft_strdup(const char *s);

#endif
