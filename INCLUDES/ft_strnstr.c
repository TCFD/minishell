/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:43:49 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/23 15:01:18 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	i;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		a = 0;
		while (big[i + a] == little[a] && (i + a) < len)
		{
			a++ ;
			if (little[a] == '\0')
				return ((char *)big + i);
		}
		i++ ;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*s1 = "abcabcd", *s2 = "abcd";
	printf("%s\n", ft_strnstr(s1, s2, 7));
	return (0);
}
*/
