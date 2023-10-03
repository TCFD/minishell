/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:28:15 by rciaze            #+#    #+#             */
/*   Updated: 2023/10/03 14:43:36 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_garbage	*start_garbage(void)
{
	t_garbage	garbage;

	garbage.head = NULL;
	garbage.len_of_lst = 0;
	return (&garbage);
}

t_garbage_lst	*new_elmt(void **pointer_to)
{
	t_garbage_lst	new;

	if (!pointer_to)
		new.pointer = NULL;
	else
		new.pointer = pointer_to;
	new.next = NULL;
	return (&new);
}

void	garbage_add(t_garbage *garbage, t_garbage_lst *new)
{
	new->next = garbage->head;
	garbage->head = new;
	garbage->len_of_lst++;
}

void	free_garbage(t_garbage *garbage)
{
	int	i;

	i = -1;
	while (++i < garbage->len_of_lst)
	{
		if (garbage->head[i].pointer)
			free(garbage->head[i].pointer);
	}
}
