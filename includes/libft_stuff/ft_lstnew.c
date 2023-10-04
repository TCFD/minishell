/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:03:18 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 14:23:47 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/minishell.h"
#include <stdlib.h>

t_list	*ft_lstnew(char *content, char type)
{
	t_list	*str;

	str = ft_calloc(sizeof(t_list), 1);
	if (!str)
		return (NULL);
	//garbage_add((void *)str);
	if (!content[0])
		str->content = NULL;
	else
		str->content = content;
	str->type = type;
	str->next = NULL;
	return (str);
}
