/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:48:48 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/05 18:10:20 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long int	ft_atoi(const char *nptr)
{
	long long int	i;
	long long int	res;
	long long int	s;

	i = 0;
	if (!nptr)
		return (malloc_failure(), 1);
	while (nptr[i] == ' ' || (nptr[i] >= 7 && nptr[i] <= 13))
		i++ ;
	res = 0;
	s = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - 48);
		i++ ;
	}
	return (res * s);
}
