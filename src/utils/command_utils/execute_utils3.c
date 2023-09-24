/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:35:49 by wolf              #+#    #+#             */
/*   Updated: 2023/09/24 17:36:08 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cmd_exist(t_cmd_and_opt *cmdopt)
{
	free(cmdopt->opt_ty_tb.tab[0]);
	cmdopt->opt_ty_tb.tab[0] = ft_strdup(cmdopt->command_name);
	if (!go_to_cmd(cmdopt))
		return (0);
	return (1);
}
