/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:41:13 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/14 16:22:55 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heck_if_same(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

char	*get_char_until_limit(char *str, int lim)
{
	char	*new_one;
	int		idx;
	int		b;

	b = 0;
	if (lim < 0)
		b = 1;
	new_one = malloc((lim + b + 1) * sizeof(char));
	if (!new_one)
		return (NULL);
	idx = 0;
	while (idx < lim)
	{
		new_one[idx] = str[idx];
		idx++;
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

int	check_if_ifs(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	stack_cpy(char *tab_stack, char *tab_heap)
{
	size_t	len_tab_heap;

	len_tab_heap = ft_strlen(tab_heap) + 1;
	if (len_tab_heap >= 1024)
		return ((void)ft_printf("Allocation Error : len(tab_heap) >= 1024\n"));
	ft_strlcpy(tab_stack, tab_heap, len_tab_heap);
}