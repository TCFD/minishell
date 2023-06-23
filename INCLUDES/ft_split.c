/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:13:25 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/23 16:07:44 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

int	verif_charset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

int	compte_mot(char *str, char charset)
{
	int		i;
	int		b;
	int		mot;

	i = 0;
	b = 0;
	mot = 0;
	while (str[i])
	{
		if (verif_charset(str[i], charset))
			b = 0;
		else
		{
			if (b == 0)
				mot++ ;
			b = 1;
		}
		i++;
	}
	if (!mot)
		return (1);
	return (mot);
}

char	*remplit_mot(char *str, char charset, int *cut)
{
	int		i;
	int		a;
	char	*tab;

	i = 0;
	while (str[i] && !verif_charset(str[i], charset))
		i++ ;
	tab = malloc((i + 1) * sizeof(char));
	if (!tab)
		free(tab);
	a = 0;
	while (a < i)
	{
		tab[a] = str[a];
		a++;
	}
	tab[a] = '\0';
	*cut = i + 1;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		a;
	int		cut;
	int		mot;
	char	**tab;
	char	*nwstr;

	nwstr = (char *)s;
	mot = compte_mot(nwstr, c);
	tab = malloc((mot + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	a = 0;
	while (mot)
	{
		while (*nwstr == c)
			nwstr++;
		tab[a] = remplit_mot(nwstr, c, &cut);
		nwstr = nwstr + cut;
		mot-- ;
		a++ ;
	}
	tab[a] = NULL;
	return (tab);
}
