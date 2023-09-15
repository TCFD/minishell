/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:43:49 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/15 18:13:54 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	i;

	if (little[0] == '\0')
		return ((char *)big);
	if (!big)
		return (NULL);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		a = 0;
		while (big[i + a] == little[a] && (i + a) < len)
		{
			a++ ;
			if (little[a] == '\0')
				return ((char *)big + i + a - 1);
		}
		i++ ;
	}
	return (NULL);
}
