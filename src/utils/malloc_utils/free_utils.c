/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:13:56 by wolf              #+#    #+#             */
/*   Updated: 2023/10/03 21:14:25 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_d_int(int **elmt, int len)
{
	int	idx;

	idx = 0;
	if (elmt != NULL)
	{
		while (idx < len)
		{
			//free(elmt[idx]);
			idx++ ;
		}
	}
	//free(elmt);
}

void	free_d_array(char **str)
{
	int	idx;
	int	len;

	len = d_len(str);
	if (str == NULL)
		return ;
	idx = 0;
	while (str[idx] && idx < len)
	{
//		//free(str[idx]);
//		str[idx] = NULL;
		idx++ ;
	}
	//free(str);
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
	//free(str);
}

void	free_cmdopt(t_cmd_and_opt *cmdopt)
{
	if (cmdopt->command_name)
		////free(cmdopt->command_name);
	if (cmdopt->command_path)
//		//free(cmdopt->command_path);
	if (cmdopt->opt_ty_tb.type)
		//free(cmdopt->opt_ty_tb.type);
	if (cmdopt->opt_ty_tb.tab != NULL)
		free_d_array(cmdopt->opt_ty_tb.tab);
	init_cmdopt(cmdopt);
}

void	free_everything(t_cmd_and_opt *cmdopt, bool f_cmdopt)
{
	if (f_cmdopt == true)
		free_cmdopt(cmdopt);
	update_pwd(NULL);
	//free(get_env_pwd());
	//free(get_env_oldpwd());
	//free(get_home_path());
	//free(get_username());
	free_prompt_last_entry();
	free_env_singleton();
}
