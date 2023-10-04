/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:48:27 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 14:15:16 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../../includes/minishell.h"

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
