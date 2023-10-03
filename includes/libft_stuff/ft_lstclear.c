/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:27:36 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/03 20:58:49 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*d_list;
	int		i;

	if (lst == NULL)
		return ;
	i = ft_lstsize(*lst);
	d_list = *(lst);
	while (i-- > 0)
	{
//		free(d_list->content);
		temp = d_list->next;
		free(d_list);
		d_list = temp;
	}
	*lst = NULL;
}
