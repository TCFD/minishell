/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:25:33 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/14 15:44:17 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++ ;
	return (i);
}
