/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:33:45 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/26 16:25:17 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	verif(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++ ;
	}
	return (0);
}

int	idxstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (verif(s1[i], (char *)set))
		i++;
	return (i);
}

int	idxend(int s1_len, char const *s1, char const *set)
{
	int	a;

	a = 1;
	while (verif(s1[s1_len - a], (char *)set))
		a++;
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s1_len;
	int		i;
	int		a;
	int		b;
	char	*tab;

	s1_len = ft_strlen((char *)s1);
	i = idxstart(s1, set);
	a = idxend(s1_len, s1, set);
	if (i == (a - 1) && i == s1_len)
		return ("");
	tab = malloc(((s1_len - (a - 1) - i) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	b = i;
	while (i <= (s1_len - a))
	{
		tab[i - b] = s1[i];
		i++ ;
	}
	tab[i - b] = '\0';
	return (tab);
}
