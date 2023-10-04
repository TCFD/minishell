/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:56:52 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 14:23:47 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**double_a_realloc(char **array, char *new_elmt)
{
	char	**new_one;
	int		idx;
	int		len;

	len = 0;
	if (array != NULL)
		len = d_len(array);
	new_one = ft_malloc((len + 2) * sizeof(char *));
	//garbage_add((void *)new_one);
	if (!new_one)
	{
		free_d_array(array);
		return (NULL);
	}
	idx = -1;
	while (++idx < len)
		new_one[idx] = ft_strdup(array[idx]);
	new_one[idx] = new_elmt;
	new_one[idx + 1] = NULL;
	return (new_one);
}

char	**ft_d_strdup(char **tab)
{
	char	**new_one;
	int		idx;
	int		sub_idx;

	idx = -1;
	new_one = ft_malloc((d_len(tab) + 1) * sizeof(char *));
	if (!new_one)
		return (NULL);
	while (tab[++idx])
	{
		sub_idx = -1;
		new_one[idx] = ft_malloc((ft_strlen(tab[idx]) + 1) * sizeof(char));
		if (!new_one[idx])
		{
			while (--idx >= 0)
				free(new_one[idx]);
			free(new_one);
			return (NULL);
		}
		while (tab[idx][++sub_idx])
			new_one[idx][sub_idx] = tab[idx][sub_idx];
		new_one[idx][sub_idx] = '\0';
	}
	new_one[idx] = NULL;
	return (new_one);
}
