/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:31:23 by wolf              #+#    #+#             */
/*   Updated: 2023/09/29 20:07:16 by rciaze           ###   ########.fr       */
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
			export_var("ANIM_=1", false, get_env());
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
		{
			bf_prd("\n➜ Outstanding \e[5m🙏\e[0m",
				ANIME_TIME, ANIM_C);
			bf_prd(" ?\n\n", ANIME_TIME, ANIM_C);
		}
		env_var_minus_one("ANIM_");
	}
}
