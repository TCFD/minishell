/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:10:57 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 14:20:48 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../../includes/minishell.h"

char	*fill_it(int size, int sign, int n)
{
	int		i;
	int		first_pos;
	char	*tab;

	tab = ft_malloc((size + sign + 1) * sizeof(char));
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

char	*ft_itoa(int n)
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
	return (fill_it(i, sign, nsave));
}
