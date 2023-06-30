/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:35:44 by wolf              #+#    #+#             */
/*   Updated: 2023/06/30 14:27:01 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmdopt(t_cmd_and_opt *cmdopt)
{
	cmdopt->command_name = NULL;
	cmdopt->command_path = NULL;
	cmdopt->opt_tab = NULL;
}
