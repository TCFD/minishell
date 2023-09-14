/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:12:32 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/21 16:23:57 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	int		end;
	char	*tab;

	end = 0;
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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	str = ft_strdup((const char *)s);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, str[i]);
		i++ ;
	}
	return (str);
}
