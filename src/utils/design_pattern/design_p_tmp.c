/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:58:36 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 17:13:00 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_prompt(char *new_prompt)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	singleton2->prompt = new_prompt;
}

char	*get_prompt(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	return (singleton2->prompt);
}

void	update_last_entry(char *last_entry)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	singleton2->l_ety = last_entry;
}

char	*get_last_entry(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	return (singleton2->l_ety);
}
