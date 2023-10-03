/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:48:27 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/03 20:56:30 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	int		end;
	char	*tab;

	end = 0;
	if (!s)
		return (ft_strdup(""));
	while (s[end])
		end++ ;
	tab = malloc(end + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < end + 1)
	{
		tab[i] = s[i];
		i++ ;
	}
	return (tab);
}
