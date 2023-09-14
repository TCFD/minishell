/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:02:41 by wolf              #+#    #+#             */
/*   Updated: 2023/09/14 16:22:14 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_len(char **str)
{
	int	idx;

	idx = 0;
	if (!str)
		return (0);
	while (str[idx])
		idx++ ;
	return (idx);
}

int	t_len(char ***str)
{
	int	idx;

	idx = 0;
	if (!str)
		return (0);
	while (str[idx])
		idx++ ;
	return (idx);
}
