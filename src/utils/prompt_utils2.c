/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:46:13 by wolf              #+#    #+#             */
/*   Updated: 2023/09/16 15:31:36 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_username_prompt(char *username)
{
	char	*shlvl_value;

	if (ft_getenv("SHLVL"))
	{
		shlvl_value = ft_join(ft_strdup("\e[32m (\e[0m"),
				ft_join(ft_strdup(ft_getenv("SHLVL")),
					ft_strdup("\e[32m)\e[0m")));
	}
	else
		shlvl_value = ft_strdup("");
	username = stick_color(ft_join(ft_strdup(username),
				ft_strdup("@minishell42")), ft_strdup(BLUE_1));
	username = ft_join(ft_strdup("\e[32m┌──(\e[0m"), username);
	username = ft_join(username, shlvl_value);
	username = ft_join(username, ft_strdup("\e[32m)-[\e[0m"));
	return (username);
}

char	*build_prompt(int u_len, char *builded_username, char *building_result)
{
	char	*r;

	r = building_result;
	r = ft_join(r, ft_strdup("\n\e[32m└─\e[0m"));
	if (g_error_code == 0 || get_last_sign() == 130)
		r = ft_join(r, ft_strdup("\e[34m➤ "));
	else
		r = ft_join(r, ft_strdup("\e[31;1m➤ "));
	if (u_len == 0)
		r = stick_color(ft_join(ft_strdup(""), r), ft_strdup(CD_C));
	else
		r = stick_color(ft_join(ft_strdup("~"), r), ft_strdup(CD_C));
	r = ft_join(builded_username, r);
	return (r);
}
