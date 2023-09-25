/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:46:13 by wolf              #+#    #+#             */
/*   Updated: 2023/09/25 16:20:06 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_username_prompt(char *username)
{
	char	*shlvl_value;

	shlvl_value = ft_getenv("SHLVL");
	if (shlvl_value && ft_atoi(shlvl_value) >= 0)
	{
		shlvl_value = ft_join(ft_strdup("\001\e[32m\002 (\001\e[0m\002"),
				ft_join(ft_strdup(ft_getenv("SHLVL")),
					ft_strdup("\001\e[32m\002)\001\e[0m\002")));
	}
	else
		shlvl_value = ft_strdup("");
	username = stick_color(ft_join(ft_strdup(username),
				ft_strdup("@minishell42")), ft_strdup(BLUE_1));
	username = ft_join(ft_strdup("\001\e[32m\002┌──(\001\e[0m\002"), username);
	username = ft_join(username, shlvl_value);
	username = ft_join(username, ft_strdup("\001\e[32m\002)-[\001\e[0m\002"));
	return (username);
}

char	*build_prompt(int u_len, char *builded_username, char *building_result)
{
	char	*r;

	r = building_result;
	r = ft_join(r, ft_strdup("\n\001\e[32m\002└─\001\e[0m\002"));
	if (g_error_code == 0 || get_last_sign() == 130)
		r = ft_join(r, ft_strdup("\001\e[34m\002➤ "));
	else
		r = ft_join(r, ft_strdup("\001\e[31;1m\002➤ "));
	if (u_len == 0)
		r = stick_color(ft_join(ft_strdup(""), r), ft_strdup(CD_C));
	else
		r = stick_color(ft_join(ft_strdup("~"), r), ft_strdup(CD_C));
	r = ft_join(builded_username, r);
	return (r);
}
