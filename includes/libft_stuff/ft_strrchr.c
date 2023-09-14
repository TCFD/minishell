/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:28:48 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/23 14:38:30 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*strcv;

	strcv = (char *)s;
	i = 0;
	while (strcv[i])
		i++ ;
	while (i + 1 > 0)
	{
		if (strcv[i] == c % 128)
			return (strcv + i);
		i-- ;
	}
	return (NULL);
}
