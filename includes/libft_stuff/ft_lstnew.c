/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:03:18 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/28 21:42:53 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(char *content, char type)
{
	t_list	*str;

	str = ft_calloc(sizeof(t_list), 1);
	if (!str)
		return (NULL);
	if (!content[0])
		str->content = NULL;
	else
		str->content = content;
	str->type = type;
	str->next = NULL;
	return (str);
}
