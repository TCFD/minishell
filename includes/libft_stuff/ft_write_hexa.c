/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:27:28 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/26 14:53:41 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	size_integer(unsigned int integer)
{
	int	count_len;

	count_len = 0;
	while (integer > 0)
	{
		count_len++ ;
		integer /= 10;
	}
	return (count_len);
}

int	size_str(char *str)
{
	int	count_len;

	count_len = 0;
	while (str[count_len])
		count_len++ ;
	return (count_len);
}

int	write_hexa(char *base, unsigned int integer, t_buff *buff_struct)
{
	int		idx;
	int		len_integer;
	char	*hexa;

	len_integer = size_integer(integer);
	if (integer == 0)
	{
		len_integer = write_char('0', buff_struct);
		return (len_integer);
	}
	if (len_integer == 1 || len_integer == 2)
		len_integer++ ;
	hexa = malloc(len_integer * sizeof(char));
	if (!hexa)
		return (0);
	idx = 0;
	while (integer > 0)
	{
		hexa[idx++] = base[integer % 16];
		integer /= 16;
	}
	hexa[idx] = '\0';
	len_integer = write_str_reverse(hexa, buff_struct);
	free(hexa);
	return (len_integer);
}

int	size_malloc(int len_base, long long unsigned int integer)
{
	int	i;

	i = 0;
	while (integer > 0)
	{
		i++ ;
		integer /= len_base;
	}
	return (i);
}

int	write_addr(void *pointeur, char *base, t_buff *buff_struct)
{
	long long unsigned int		recupaddr;
	int							len;
	int							count;
	char						*tab;

	if (!pointeur)
		return (write_str("(nil)", buff_struct));
	if ((long long int)pointeur == -1)
		return (write_str("0xffffffffffffffff", buff_struct));
	recupaddr = (long long unsigned int)pointeur;
	tab = malloc((size_malloc(size_str(base), recupaddr) + 1) * sizeof(char));
	if (!tab)
		return (0);
	count = 0;
	while (recupaddr > 0)
	{
		tab[count] = base[recupaddr % size_str(base)];
		recupaddr /= size_str(base);
		count++ ;
	}
	tab[count] = '\0';
	write_str("0x", buff_struct);
	len = write_str_reverse(tab, buff_struct);
	free(tab);
	return (len + 2);
}
