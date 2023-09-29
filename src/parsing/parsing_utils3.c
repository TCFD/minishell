/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:32:34 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/29 14:39:46 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lst_add(t_list **list, char **content, char type)
{
	(*list)->content = ft_strdup(*content);
	if (!(*list)->content)
		return (malloc_fail(), 1);
	free(*content);
	if (!(*list)->content)
		return (0);
	(*list)->type = type;
	(*list)->next = ft_lstnew("", NONE);
	if (!(*list)->next)
		return (0);
	(*list) = (*list)->next;
	return (1);
}
