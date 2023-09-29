/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:35:49 by wolf              #+#    #+#             */
/*   Updated: 2023/09/28 21:56:52 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cmd_exist(t_cmd_and_opt *cmdopt)
{
	free(cmdopt->opt_ty_tb.tab[0]);
	cmdopt->opt_ty_tb.tab[0] = ft_strdup(cmdopt->command_name);
	if (!cmdopt->opt_ty_tb.tab[0])
		return (free_cmdopt(cmdopt), malloc_fail(), 1);
	if (!go_to_cmd(cmdopt))
		return (0);
	return (1);
}

int	cmp(char *cmd_name, char *cmd_name_2)
{
	if (ft_strncmp(cmd_name, cmd_name_2, ft_strlen(cmd_name_2)) == 0
		&& ft_strlen(cmd_name) == ft_strlen(cmd_name_2))
		return (1);
	return (0);
}
