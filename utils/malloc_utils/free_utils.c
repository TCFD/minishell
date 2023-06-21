/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:13:56 by wolf              #+#    #+#             */
/*   Updated: 2023/06/21 15:09:15 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_d_array(char **str)
{
	int	idx;

	idx = 0;
	if (str == NULL || str[idx] == NULL)
		return (free(str));
	while (str[idx] != NULL)
	{
		free(str[idx]);
		idx++ ;
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
	free(cmdopt->option.type);
	free_d_array(cmdopt->option.opt_tab);
}
