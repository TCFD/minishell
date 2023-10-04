/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:13:56 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 16:57:41 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_d_int(int **elmt, int len)
{
	int	idx;

	idx = 0;
	if (elmt != NULL)
	{
		while (idx < len)
			idx++ ;
	}
}

void	free_d_array(char **str)
{
	int	idx;
	int	len;

	len = d_len(str);
	if (str == NULL)
		return ;
	idx = 0;
	while (str[idx] && idx < len)
		idx++ ;
}

