/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:10:57 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/05 18:12:01 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../../includes/minishell.h"

int	how_many_digits(long long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(long long int n)
{
	int		boolean;
	char	*str;
	int		i;

	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	boolean = 0;
	i = how_many_digits(n) - 1;
	str = ft_malloc((i + 1) * sizeof(char));
	str[i + 1] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		boolean = 1;
		n = -n;
	}
	while (i >= boolean)
	{
		str[i] = (char)(n % 10 + 48);
		n = n / 10;
		i--;
	}
	return (str);
}
