/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:01:40 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/11 12:37:01 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*srccpy;

	i = 0;
	srccpy = (char *)src;
	while (i < n)
	{
		((char *)dest)[i] = srccpy[i];
		i++ ;
	}
	return (dest);
}
