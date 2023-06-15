/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:02:43 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/17 14:36:03 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++ ;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	if (size == 0)
		return (ft_strlen((char *)src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++ ;
	}
	dst[i] = '\0';
	return (ft_strlen((char *)src));
}
