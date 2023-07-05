/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:13:56 by wolf              #+#    #+#             */
/*   Updated: 2023/07/05 17:33:20 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_d_array(char **str)
{
	int idx;
	
	idx = 0;
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
	if (cmdopt->command_name)
		free(cmdopt->command_name);
	if (cmdopt->command_path)
		free(cmdopt->command_path);
	if (cmdopt->opt_and_type_tab.type)
		free(cmdopt->opt_and_type_tab.type);
	if (cmdopt->opt_and_type_tab.tab)
		free_d_array(cmdopt->opt_and_type_tab.tab);
	cmdopt->command_name = NULL;
	cmdopt->command_path = NULL;
	cmdopt->opt_and_type_tab.type = NULL;
	cmdopt->opt_and_type_tab.tab = NULL;
}
