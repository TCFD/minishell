/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:46:29 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/28 13:09:30 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &(str[i]), 1);
		i++ ;
	}
	return (i);
}

int	write_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	write_int(int nb)
{
	int		len;
	char	*tab;

	tab = int_ft_itoa(nb);
	len = write_str(tab);
	free(tab);
	return (len);
}

int	write_unsigned_int(unsigned int nb)
{
	int		len;
	char	*tab;

	tab = unsigned_ft_itoa(nb);
	len = write_str(tab);
	free(tab);
	return (len);
}

int	write_str_reverse(char *str)
{
	int		len_str;
	int		idx;

	len_str = 0;
	while (str[len_str])
		len_str++ ;
	idx = 0;
	while (str[idx])
	{
		write_char(str[len_str - (idx + 1)]);
		idx++ ;
	}
	return (idx);
}
