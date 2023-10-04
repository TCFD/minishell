/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:12:32 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 14:15:33 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		end;
	char	*tab;

	end = 0;
	while (s[end])
		end++ ;
	tab = ft_malloc(end + 1);
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
