/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:10:57 by tboldrin          #+#    #+#             */
/*   Updated: 2022/12/14 15:59:28 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_power(int a, int b)
{
	int	i;
	int	res;

	i = 1;
	res = a;
	while (i < b)
	{
		res *= a;
		i++ ;
	}
	return (res);
}

char	*int_fill_it(int size, int sign, int n)
{
	int		i;
	int		first_pos;
	char	*tab;

	tab = malloc(1 + (size + sign) * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	if (sign == 1)
	{
		tab[i] = '-';
		i++ ;
	}
	while ((i - sign) < size)
	{
		if ((i - sign) + 1 != size)
			first_pos = ft_power(10, size - ((i - sign) + 1));
		else
			first_pos = 1;
		tab[i] = '0' + (n / first_pos);
		n -= (n / first_pos) * first_pos;
		i++ ;
	}
	tab[i] = '\0';
	return (tab);
}

char	*unsigned_int_fill_it(int size, unsigned int n)
{
	int		i;
	int		first_pos;
	char	*tab;

	tab = malloc(1 + (size) * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (i + 1 != size)
			first_pos = ft_power(10, size - (i + 1));
		else
			first_pos = 1;
		tab[i] = '0' + (n / first_pos);
		n -= (n / first_pos) * first_pos;
		i++ ;
	}
	tab[i] = '\0';
	return (tab);
}

char	*int_ft_itoa(int n)
{
	int	i;
	int	sign;
	int	nsave;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	nsave = n;
	i = 0;
	while (n >= 1)
	{
		i++ ;
		n /= 10;
	}
	return (int_fill_it(i, sign, nsave));
}

char	*unsigned_ft_itoa(unsigned int n)
{
	int	i;
	int	nsave;

	if (n == 0)
		return (ft_strdup("0"));
	nsave = n;
	i = 0;
	while (n >= 1)
	{
		i++ ;
		n /= 10;
	}
	return (unsigned_int_fill_it(i, nsave));
}
