/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:32:00 by rciaze            #+#    #+#             */
/*   Updated: 2023/10/03 21:38:54 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strdup_protect(char *str)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (!new_str)
		return (malloc_failure(), NULL);
	garbage_add((void *)new_str);
	return (new_str);
}

char	*ft_substr_protect(char *str, int start, int len)
{
	char	*new_str;

	new_str = ft_substr(str, start, len);
	if (!new_str)
		return (malloc_failure(), NULL);
	garbage_add((void *)new_str);
	return (new_str);
}

char	**ft_split_protect(char *str, char c)
{
	char	**new_split;

	new_split = ft_split(str, c);
	if (!new_split)
		return (malloc_failure(), NULL);
	add_d_t_garbage((void **)(new_split), d_len(new_split));
	garbage_add_triple((void **)(new_split));
	return (new_split);
}

