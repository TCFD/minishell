/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:59:40 by rciaze            #+#    #+#             */
/*   Updated: 2023/02/03 16:35:03 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	how_many_words(char const *s, char c, int i)
{
	int	words_count;
	int	j;

	words_count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			if (c == ' ' && s[i - 1] == '\'')
			{
				j = i;
				while (s[i] != '\'' && s[i])
					i++;
				if (s[i++] != '\'')
					i = j;
			}
		}
		if (s[i - 1] != c)
			words_count++;
	}
	return (words_count);
}

void	free_all(char **str, int wordc)
{
	int	i;

	i = 0;
	while (i <= wordc)
		free(str[i]);
	free(str);
}

char	**attribution(char const *s, char **str, t_split my_s)
{
	while (++my_s.j < my_s.wordc)
	{
		my_s.len = 0;
		while (s[my_s.i] == my_s.c && s[my_s.i++])
			my_s.start = my_s.i;
		while (s[my_s.i] != my_s.c && s[my_s.i++] && ++my_s.len)
		{
			if (my_s.c == ' ' && s[my_s.i - 1] == '\'')
			{
				my_s.k = my_s.i;
				while (s[my_s.i] != '\'' && s[my_s.i++])
					my_s.len++;
				if (s[my_s.i++] != '\'')
					my_s.i = my_s.k;
				else
					if (my_s.start++)
						my_s.len--;
			}
		}
		str[my_s.j] = ft_substr(s, my_s.start, my_s.len);
		if (!str[my_s.j])
			return (free_all(str, my_s.wordc), NULL);
	}
	str[my_s.j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**fs;
	t_split	my_s;

	my_s.wordc = how_many_words(s, c, 0);
	my_s.c = c;
	my_s.len = 0;
	my_s.start = 0;
	my_s.i = 0;
	my_s.j = -1;
	fs = malloc((my_s.wordc + 1) * sizeof(char *));
	if (!fs)
		return (NULL);
	return (attribution(s, fs, my_s));
}
