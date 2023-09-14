/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:17:29 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/17 13:27:31 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest1;
	const unsigned char	*src1;

	dest1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	i = 0;
	if (src1 < dest1)
	{
		while (++i <= n)
		{
			dest1[n - i] = src1[n - i];
		}
	}
	else
		while (n-- > 0)
			*(dest1++) = *(src1++);
	return (dst);
}
