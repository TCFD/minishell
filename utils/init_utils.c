/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:35:44 by wolf              #+#    #+#             */
/*   Updated: 2023/09/10 17:13:05 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmdopt(t_cmd_and_opt *cmdopt)
{
	cmdopt->command_name = NULL;
	cmdopt->command_path = NULL;
	cmdopt->opt_ty_tb.type = NULL;
	cmdopt->opt_ty_tb.tab = NULL;
	cmdopt->path_unset = 0;
}

void	init_design_pattern(t_singleton *design_p)
{
	design_p->username = NULL;
	design_p->env = NULL;
}
