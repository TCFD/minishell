/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:46:29 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/24 20:58:30 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_str(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(fd, &(str[i]), 1);
		i++ ;
	}
	return (i);
}

int	write_char(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	write_int(int nb, int fd)
{
	int		len;
	char	*tab;

	tab = int_ft_itoa(nb);
	len = write_str(tab, fd);
	free(tab);
	return (len);
}

int	write_unsigned_int(unsigned int nb, int fd)
{
	int		len;
	char	*tab;

	tab = unsigned_ft_itoa(nb);
	len = write_str(tab, fd);
	free(tab);
	return (len);
}

int	write_str_reverse(char *str, int fd)
{
	int		len_str;
	int		idx;

	len_str = 0;
	while (str[len_str])
		len_str++ ;
	idx = 0;
	while (str[idx])
	{
		write_char(str[len_str - (idx + 1)], fd);
		idx++ ;
	}
	return (idx);
}
