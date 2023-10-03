/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:58:36 by wolf              #+#    #+#             */
/*   Updated: 2023/10/03 21:14:25 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_prompt(char *new_prompt)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
//	if (singleton2->prompt != NULL)
//		//free(singleton2->prompt);
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
//	if (singleton2->l_ety != NULL)
//		//free(singleton2->l_ety);
	singleton2->l_ety = last_entry;
}

char	*get_last_entry(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	return (singleton2->l_ety);
}

void	free_prompt_last_entry(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	(void)(singleton2);
//	//free(singleton2->prompt);
//	//free(singleton2->l_ety);
	init_prompt_last_entry();
}
