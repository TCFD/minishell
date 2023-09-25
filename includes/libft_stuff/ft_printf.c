/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:33:27 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/24 20:59:15 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_it(char c, va_list arg, int fd)
{
	int		len;

	if (c == 'c')
		len = write_char(va_arg(arg, int), fd);
	if (c == 's')
		len = write_str(va_arg(arg, char *), fd);
	if (c == 'p')
		len = write_addr(va_arg(arg, void *), "0123456789abcdef", fd);
	if (c == 'd' || c == 'i')
		len = write_int(va_arg(arg, int), fd);
	if (c == 'u')
		len = write_unsigned_int(va_arg(arg, int), fd);
	if (c == 'x')
		len = write_hexa("0123456789abcdef", va_arg(arg, unsigned int), fd);
	if (c == 'X')
		len = write_hexa("0123456789ABCDEF", va_arg(arg, unsigned int), fd);
	if (c == '%')
		len = write(fd, "%", 1);
	return (len);
}

int	ft_printf(int fd, const char *fmt, ...)
{
	va_list	arg;
	int		i;
	int		counter;

	va_start(arg, fmt);
	i = 0;
	counter = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++ ;
			counter += write_it(fmt[i], arg, fd) - 2;
			i++ ;
		}
		else
		{
			write(fd, &fmt[i], 1);
			i++ ;
		}
	}
	va_end(arg);
	return (i + counter);
}
