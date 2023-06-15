/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:20:25 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/28 14:41:45 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++ ;
	}
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*str;

	if (!nmeb || !size)
		return (NULL);
	if (__SIZE_MAX__ / nmeb > size)
	{
		str = (void *)malloc(nmeb * size);
		if (!str)
			return (NULL);
	}
	else
		return (NULL);
	ft_bzero(str, nmeb * size);
	return (str);
}
