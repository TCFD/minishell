/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:33:27 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/26 15:02:54 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	is_buff_full(t_buff *buff_struct)
{
	if (buff_struct->buff_i == 4095)
	{
		buff_struct->buff[buff_struct->buff_i] = '\0';
		write(buff_struct->fd, buff_struct->buff, buff_struct->buff_i);
		buff_struct->buff_i = 0;
	}
}

int	write_it(char c, va_list arg, t_buff *buff_struct)
{
	int		len;

	if (c == 'c')
		len = write_char(va_arg(arg, int), buff_struct);
	if (c == 's')
		len = write_str(va_arg(arg, char *), buff_struct);
	if (c == 'p')
		len = write_addr(va_arg(arg, void *), "0123456789abcdef", buff_struct);
	if (c == 'd' || c == 'i')
		len = write_int(va_arg(arg, int), buff_struct);
	if (c == 'u')
		len = write_unsigned_int(va_arg(arg, int), buff_struct);
	if (c == 'x')
		len = write_hexa("0123456789abcdef", va_arg(arg, unsigned int),
				buff_struct);
	if (c == 'X')
		len = write_hexa("0123456789ABCDEF", va_arg(arg, unsigned int),
				buff_struct);
	if (c == '%')
	{
		buff_struct->buff[buff_struct->buff_i++] = '%';
		len = 1;
	}
	return (len);
}

void	init_printf(int *i, int *counter, t_buff *buff_struct, int fd)
{
	*i = -1;
	*counter = 0;
	buff_struct->buff_i = 0;
	buff_struct->fd = fd;
}

int	ft_printf(int fd, const char *fmt, ...)
{
	va_list	arg;
	int		i;
	int		counter;
	t_buff	buff_struct;

	va_start(arg, fmt);
	init_printf(&i, &counter, &buff_struct, fd);
	while (fmt[++i])
	{
		if (fmt[i] == '%')
		{
			i++ ;
			counter += write_it(fmt[i], arg, &buff_struct) - 2;
		}
		else
		{
			is_buff_full(&buff_struct);
			buff_struct.buff[buff_struct.buff_i++] = fmt[i];
		}
	}
	buff_struct.buff[buff_struct.buff_i] = '\0';
	write(buff_struct.fd, buff_struct.buff, buff_struct.buff_i);
	va_end(arg);
	return (i + counter);
}
