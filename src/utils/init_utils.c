/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:35:44 by wolf              #+#    #+#             */
/*   Updated: 2023/09/14 16:22:55 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cmdopt(t_cmd_and_opt *cmdopt)
{
	cmdopt->command_name = NULL;
	cmdopt->command_path = NULL;
	cmdopt->opt_ty_tb.type = NULL;
	cmdopt->opt_ty_tb.tab = NULL;
	cmdopt->tmp_utils.l_ety = NULL;
	cmdopt->tmp_utils.prompt = NULL;
	cmdopt->path_unset = 0;
}
