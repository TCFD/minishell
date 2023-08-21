/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:37:39 by tboldrin          #+#    #+#             */
/*   Updated: 2023/08/21 19:07:38 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
			
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			if ((unsigned char)s1[i] < (unsigned char)s2[i])
				return (-1);
			else
				return (1);
		}
	}
	return (0);
}
