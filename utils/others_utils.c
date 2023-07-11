/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:41:13 by tboldrin          #+#    #+#             */
/*   Updated: 2023/07/05 19:56:16 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heck_if_same(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

char	*get_char_until_limit(char *str, int lim)
{
	char	*new_one;
	int		idx;

	new_one = malloc((lim + 1) * sizeof(char));
	if (!new_one)
		return (NULL);
	idx = 0;
	while (idx < lim)
	{
		new_one[idx] = str[idx];
		idx++ ;	
	}
	new_one[idx] = '\0';
	free(str);
	return (new_one);
}

int	find_first_occurence(char *str, char cara)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == cara)
			return (idx);
		idx++ ;
	}
	return (-1);
}