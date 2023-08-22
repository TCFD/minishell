/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:13:56 by wolf              #+#    #+#             */
/*   Updated: 2023/08/22 12:46:17 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_d_int(int **elmt, int len)
{
	int	idx;

	idx = 0;
	if (elmt != NULL)
	{
		while (idx < len)
		{
        	free(elmt[idx]);
			idx++ ;
		}
	}
    free(elmt);
}


void	free_d_array(char **str)
{
	int idx;
	int len;

	len = d_len(str);
	if (str == NULL)
		return;
	idx = 0;
	while (str[idx] && idx < len)
	{
		free(str[idx]);
		str[idx] = NULL;
		idx++ ;
	}
	if (len >= 1)
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
	static int	count;

	count++ ;
	if (cmdopt->command_name)
		free(cmdopt->command_name);
	if (cmdopt->command_path)
		free(cmdopt->command_path);
	if (cmdopt->opt_ty_tb.type)
	{
		//printf("trying to free : ..->opt_ty_tb.type\n");
		free(cmdopt->opt_ty_tb.type);
	}
	if (cmdopt->opt_ty_tb.tab != NULL)
	{
		//printf("trying to free : ..->opt_ty_tb.tab\n");
		free_d_array(cmdopt->opt_ty_tb.tab);
	}
	//printf("all cmdopt'free done.\n");
	init_cmdopt(cmdopt);
}
