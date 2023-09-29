/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:46:13 by wolf              #+#    #+#             */
/*   Updated: 2023/09/29 14:39:36 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_username_prompt(char *username)
{
	char	*shlvl_value;

	shlvl_value = ft_getenv("SHLVL");
	if (shlvl_value && ft_atoi(shlvl_value) >= 0)
	{
		shlvl_value = ft_join_strdup_left("\001\e[32m (\e[0m\002",
				ft_join_strdup(ft_getenv("SHLVL"),
					"\001\e[32m\002)\001\e[0m\002"));
		if (!shlvl_value)
			return (malloc_fail(), NULL);
	}
	else
	{
		shlvl_value = ft_strdup("");
		if (!shlvl_value)
			return (malloc_fail(), NULL);
	}
	username = stick_color(ft_join_strdup(username,
				"@minishell42"), ft_strdup("\001\033[34;1m\002"));
	username = ft_join_strdup_left("\001\e[32m\002┌──(\001\e[0m\002", username);
	username = ft_join_no_strdup(username, shlvl_value);
	username = ft_join_strdup_right(username, "\001\e[32m\002)-[\001\e[0m\002");
	if (!username)
		return (malloc_fail(), NULL);
	return (username);
}

char	*build_prompt(int u_len, char *builded_username, char *building_result)
{
	char	*r;

	r = building_result;
	r = ft_join_strdup_right(r, "\n\001\e[32m\002└─\001\e[0m\002");
	if (g_error_code == 0 || get_last_sign() == 130)
		r = ft_join_strdup_right(r, "\001\e[34m\002➤ \001\e[0m");
	else
		r = ft_join_strdup_right(r, "\001\e[31;1m\002➤ \001\e[0m");
	if (u_len == 0)
		r = stick_color(ft_join_strdup_left("", r), ft_join_strdup("\001\033[37;1m", "\002"));
	else
		r = stick_color(ft_join_strdup_left("~", r), ft_join_strdup("\001\033[37;1m", "\002"));
	r = ft_join_no_strdup(builded_username, r);
	return (r);
}
