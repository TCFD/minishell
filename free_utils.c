/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:13:56 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 16:41:23 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free_d_array(str[idx]);
		idx++ ;
	}
	free(str);
}

void	free_cmdopt(t_cmd_and_opt *cmdopt)
{
	if (cmdopt->command_name != NULL)
		free(cmdopt->command_name);
	if (cmdopt->command_path != NULL)
		free(cmdopt->command_path);
	if (cmdopt->option != NULL)
		free(cmdopt->option);
		//free_d_array(cmdopt->option);
}
