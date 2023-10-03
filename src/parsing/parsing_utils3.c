/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:32:34 by rciaze            #+#    #+#             */
/*   Updated: 2023/10/03 21:34:36 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lst_add(t_list **list, char **content, char type)
{
	(*list)->content = ft_strdup_protect(*content);
	if (!(*list)->content)
		return (0);
	(*list)->type = type;
	(*list)->next = ft_lstnew("", NONE);
	if (!(*list)->next)
		return (0);
	(*list) = (*list)->next;
	return (1);
}

void	fill_cmdopt(t_cmd_and_opt *cmdopt, t_list *temp_list)
{
	int	i;

	i = 0;
	while (temp_list->next)
	{
		cmdopt->opt_ty_tb.tab[i] = ft_strdup_protect(temp_list->content);
		if (!cmdopt->opt_ty_tb.tab[i])
			return (free(cmdopt->opt_ty_tb.type), malloc_failure());
		cmdopt->opt_ty_tb.type[i] = temp_list->type;
		temp_list = temp_list->next;
		i++;
	}
	cmdopt->opt_ty_tb.tab[i] = NULL;
	cmdopt->opt_ty_tb.type[i] = '\0';
}

int	what_case_equal_c(char c, char c2)
{
	if ((c == SIMPLE_Q && c2 == SIMPLE_Q)
		|| (c == DOUBLE_Q && c2 == DOUBLE_Q))
		return (1);
	return (0);
}
