/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:18:52 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 14:21:14 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	int		c;
	char	*tab;

	a = ft_strlen((char *)s1);
	b = ft_strlen((char *)s2);
	c = -1;
	tab = ft_malloc((a + b + 1) * sizeof(char));
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
