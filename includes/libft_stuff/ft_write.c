/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:46:29 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/26 14:58:32 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_str(char *str, t_buff *buff_struct)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		is_buff_full(buff_struct);
		buff_struct->buff[buff_struct->buff_i++] = str[i];
		i++ ;
	}
	return (i);
}

int	write_char(char c, t_buff *buff_struct)
{
	is_buff_full(buff_struct);
	buff_struct->buff[buff_struct->buff_i++] = c;
	return (1);
}

int	write_int(int nb, t_buff *buff_struct)
{
	int		len;
	char	*tab;

	tab = int_ft_itoa(nb);
	len = write_str(tab, buff_struct);
	free(tab);
	return (len);
}

int	write_unsigned_int(unsigned int nb, t_buff *buff_struct)
{
	int		len;
	char	*tab;

	tab = unsigned_ft_itoa(nb);
	len = write_str(tab, buff_struct);
	free(tab);
	return (len);
}

int	write_str_reverse(char *str, t_buff *buff_struct)
{
	int		len_str;
	int		idx;

	len_str = 0;
	while (str[len_str])
		len_str++ ;
	idx = 0;
	while (str[idx])
	{
		write_char(str[len_str - (idx + 1)], buff_struct);
		idx++ ;
	}
	return (idx);
}
