/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:27:36 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/26 14:54:05 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp != NULL)
		{
			del(tmp->content);
			tmp = lst[0]->next;
			free(*lst);
			*lst = tmp;
		}
	}
	*lst = NULL;
}
