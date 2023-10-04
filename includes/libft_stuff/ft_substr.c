/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:23:21 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 14:21:37 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (!s)
		return (NULL);
	if (len == 0 || (size_t) start > ft_strlen((char *) s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = ft_malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (i - start < (unsigned int)(len) && s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
