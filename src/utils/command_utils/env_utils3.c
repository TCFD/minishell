/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:31:23 by wolf              #+#    #+#             */
/*   Updated: 2023/09/14 16:23:20 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	verif_if_env_called(t_cmd_and_opt *cmdopt)
{
	if (cmp(cmdopt->command_path, "/bin/env")
		|| cmp(cmdopt->command_path, "/usr/bin/env")
		|| cmp(cmdopt->command_name, "env"))
		return (1);
	return (0);
}

// Function to manage animation task one time. //
void	one_time_animation_start(void)
{
	char	*str;

	str = ft_getenv("ANIM_");
	if (!(str))
	{
		if (get_fix_env_detection() != 1)
		{
			welcome_to_minishell();
			export_var("ANIM_=1");
		}
	}
	else
		env_var_plus_one("ANIM_");
}

void	one_time_animation_end(void)
{
	char	*str;

	str = ft_getenv("ANIM_");
	if (str != NULL)
	{
		if (ft_atoi(str) == 1)
			bf_prd("\n➜ Outstanding \033[5m🙏\033[0m\033[32m ?\n\n",
				ANIME_TIME, GREEN);
		env_var_minus_one("ANIM_");
	}
}
