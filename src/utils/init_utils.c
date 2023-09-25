/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:35:44 by wolf              #+#    #+#             */
/*   Updated: 2023/09/25 16:30:21 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cmdopt(t_cmd_and_opt *cmdopt)
{
	cmdopt->command_name = NULL;
	cmdopt->command_path = NULL;
	cmdopt->opt_ty_tb.type = NULL;
	cmdopt->opt_ty_tb.tab = NULL;
	cmdopt->path_unset = 0;
	cmdopt->is_child = false;
}

void	init_prompt_last_entry(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	singleton2->prompt = NULL;
	singleton2->l_ety = NULL;
}

void	init_prompt_last_entry(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	singleton2->prompt = NULL;
	singleton2->l_ety = NULL;
}
