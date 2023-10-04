/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:44 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 17:26:14 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_underscore_value(t_cmd_and_opt *cmdopt, bool update_g)
{
	t_opt_tab	all_args;
	char		*var;
	char		*last_cmd;

	all_args = cmdopt->opt_ty_tb;
	if (all_args.tab != NULL)
	{
		last_cmd = all_args.tab[d_len(all_args.tab) - 1];
		if (cmp(last_cmd, "env"))
			last_cmd = "/usr/bin/env";
	}
	else
		last_cmd = "";
	var = ft_join(ft_strdup("_="), ft_strdup(last_cmd));
	export_var(var, update_g, get_env());
	return ;
}

void	change_underscore_value_void(bool update_g)
{
	char		*var;

	var = ft_join(ft_strdup("_="), ft_strdup(""));
	export_var(var, update_g, get_env());
	return ;
}
