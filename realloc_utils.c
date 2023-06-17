/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:56:52 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 19:57:34 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**double_a_realloc(char **array, char *new_elmt)
{
	char	**new_one;
	int		idx;
	int		len;

	len = 0;
	if (array != NULL)
		len = d_len(array);
	new_one = malloc((len + 2) * sizeof(char *));
	if (!new_one)
	{
		free_d_array(array);
		return (NULL);
	}
	idx = 0;
	while (idx < len)
	{
		new_one[idx] = array[idx];
		idx++ ;
	}
	new_one[idx] = ft_strdup(new_elmt);
	new_one[idx + 1] = NULL;
	free(array);
	return (new_one);
}
