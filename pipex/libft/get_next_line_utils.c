/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:38:34 by rciaze            #+#    #+#             */
/*   Updated: 2023/02/02 11:01:25 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	char				*str;

	if (!s)
		return (NULL);
	if (len == 0 || (size_t) start > ft_strlen(s))
	{
		free((void *)s);
		return (NULL);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (i - start < (unsigned int)(len) && s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free((void *)s);
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	str = malloc(((ft_strlen(s1)) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[i - ft_strlen(s1)])
	{	
		str[i] = s2[-ft_strlen(s1) + i];
		i++;
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

char	*ft_strdup_gnl(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
