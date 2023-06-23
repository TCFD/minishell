/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:18:52 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/23 15:05:19 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++ ;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	int		c;
	char	*tab;

	a = ft_strlen((char *)s1);
	b = ft_strlen((char *)s2);
	c = -1;
	tab = malloc((a + b + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (++c < a)
		tab[c] = s1[c];
	c = -1;
	while (++c < b)
		tab[c + a] = s2[c];
	tab[c + a] = '\0';
	return (tab);
}
