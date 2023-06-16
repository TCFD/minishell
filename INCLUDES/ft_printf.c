/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:33:27 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/16 15:43:52 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_it(char c, va_list arg)
{
	int		len;

	if (c == 'c')
		len = write_char(va_arg(arg, int));
	if (c == 's')
		len = write_str(va_arg(arg, char *));
	if (c == 'p')
		len = write_addr(va_arg(arg, void *), "0123456789abcdef");
	if (c == 'd' || c == 'i')
		len = write_int(va_arg(arg, int));
	if (c == 'u')
		len = write_unsigned_int(va_arg(arg, int));
	if (c == 'x')
		len = write_hexa("0123456789abcdef", va_arg(arg, unsigned int));
	if (c == 'X')
		len = write_hexa("0123456789ABCDEF", va_arg(arg, unsigned int));
	if (c == '%')
		len = write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *fmt, ...)
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
			counter += write_it(fmt[i], arg) - 2;
			i++ ;
		}
		else
		{
			write(1, &fmt[i], 1);
			i++ ;
		}
	}
	va_end(arg);
	return (i + counter);
}
