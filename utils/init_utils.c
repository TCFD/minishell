/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:35:44 by wolf              #+#    #+#             */
/*   Updated: 2023/07/04 16:09:26 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmdopt(t_cmd_and_opt *cmdopt)
{
	cmdopt->command_name = NULL;
	cmdopt->command_path = NULL;
	cmdopt->opt_ty_tb.type = NULL;
	cmdopt->opt_ty_tb.type = NULL;
}

void	init_design_pattern(t_singleton *design_p)
{
	design_p->username = NULL;
	design_p->env = NULL;
}
	
