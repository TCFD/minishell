/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:56:52 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 17:17:19 by rciaze           ###   ########.fr       */
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
	idx = -1;
	while (++idx < len)
		new_one[idx] = ft_strdup(array[idx]);
	new_one[idx] = new_elmt;
	new_one[idx + 1] = NULL;
	return (new_one);
}
