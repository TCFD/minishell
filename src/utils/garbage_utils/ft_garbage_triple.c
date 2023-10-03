/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_triple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:04:18 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/03 20:25:15 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_garbage_lst_triple	*new_elmt_triple(void **pointer_to)
{
	t_garbage_lst_triple	*new;

	new = malloc(sizeof(t_garbage_lst_triple));
	if (!new)
		malloc_failure();
	if (!pointer_to)
		new->pointer = NULL;
	else
		new->pointer = pointer_to;
	new->next = NULL;
	return (new);
}

// Doit etre call quand nouvelle allocation
void	garbage_add_triple(void **pointer)
{
	t_garbage				*garbage;
	t_garbage_lst_triple	*new;

	garbage = get_garbage();
	new = new_elmt_triple(pointer);
	if (garbage->head_triple == NULL)
	{
		garbage->head_triple = new;
		garbage->tail_triple = new;
	}
	garbage->tail_triple->next = new;
	garbage->tail_triple = garbage->tail_triple->next;
	garbage->len_of_lst_triple++;
}
