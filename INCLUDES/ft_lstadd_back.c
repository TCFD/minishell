/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:08:47 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/28 10:55:36 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*save;

	save = *lst;
	if (save == NULL)
	{
		*lst = new;
		return ;
	}
	while (save->next != NULL)
		save = save->next;
	save->next = new;
}
