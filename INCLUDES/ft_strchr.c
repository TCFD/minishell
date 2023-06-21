/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:19:19 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/21 14:20:44 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr_rc(const char *s, int c)
{
	int		i;

	if (c == '\0')
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++ ;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	if (c == '\0')
	{
		i = 0;
		while (s[i])
			i++;
		return ((char *)s + i);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++ ;
	}
	return (NULL);
}
