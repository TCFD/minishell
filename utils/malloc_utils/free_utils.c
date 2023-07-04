/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:13:56 by wolf              #+#    #+#             */
/*   Updated: 2023/07/04 16:09:26 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_d_array(char **str)
{
	int idx = 0;
	
	if (str == NULL)
		return;
	while (str[idx] != NULL)
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}

void	free_t_array(char ***str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		idx++ ;
		free_d_array(str[idx]);
	}
	free(str);
}

void	free_cmdopt(t_cmd_and_opt *cmdopt)
{
	free(cmdopt->command_name);
	free(cmdopt->command_path);
	free(cmdopt->opt_ty_tb.type);
	free_d_array(cmdopt->opt_ty_tb.tab);
}
