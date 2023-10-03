/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:46:13 by wolf              #+#    #+#             */
/*   Updated: 2023/10/03 14:32:34 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_color(char *c1, char *str, bool dup_str)
{
	char	*color_builded;

	if (dup_str)
		color_builded = ft_join_strdup(c1, str);
	if (!dup_str)
		color_builded = ft_join_strdup_left(c1, str);
	color_builded = ft_join_strdup_right(color_builded, NC);
	if (!color_builded)
		return (malloc_failure(), NULL);
	return (color_builded);
}

char	*build_username_prompt(char *username)
{
	char	*shlvl_value;

	shlvl_value = ft_getenv("SHLVL");
	if (shlvl_value && is_digit(shlvl_value) && ft_atoi(shlvl_value) >= 0)
	{
		shlvl_value = build_color(GREEN, " (", true);
		shlvl_value = ft_join_no_strdup(shlvl_value,
				build_color(NC, ft_getenv("SHLVL"), true));
		shlvl_value = ft_join_no_strdup(shlvl_value,
				build_color(GREEN, ")", true));
	}
	else
		shlvl_value = ft_strdup("");
	if (!shlvl_value)
		return (malloc_failure(), NULL);
	username = build_color(BLUE_1, ft_join_strdup(username, "@minishell42"), 0);
	username = ft_join_no_strdup(build_color(GREEN, "┌──(", true), build_color(NC, username, false));
	username = ft_join_no_strdup(username, shlvl_value);
	username = ft_join_no_strdup(username, build_color(GREEN, ")-[", true));
	if (!username)
		return (malloc_failure(), NULL);
	return (username);
}

char	*err_code_char(void)
{
	char	*tmp;

	if (g_error_code == 130)
		tmp = ft_strdup("SIGINT");
	else if (g_error_code == 131)
		tmp = ft_strdup("SIGQUIT");
	else if (g_error_code == 139)
		tmp = ft_strdup("SIGSEGV");
	else if (g_error_code == 143)
		tmp = ft_strdup("SIGTERM");
	else
		tmp = ft_itoa(g_error_code);
	if (!tmp)
		return (malloc_failure(), NULL);
	return (tmp);
	
}

char	*build_prompt(int u_len, char *builded_username, char *building_result)
{
	char	*r;
	char	*code;

	r = building_result;
	r = ft_join_no_strdup(r, build_color(GREEN, "└──", true));
	r = ft_join_strdup_right(r, NC);
	if (g_error_code == 0 || get_last_sign() == 130)
		r = ft_join_no_strdup(r, build_color(BLUE, "➤ ", true));
	else
	{
		code = ft_join_strdup_right(build_color(GREEN, "[", true), NC);
		code = ft_join_no_strdup(code, build_color(RED, err_code_char(), 0));
		code = ft_join_no_strdup(code, build_color(GREEN, "]", true));
		code = ft_join_no_strdup(code, build_color(BLUE, "➤ ", true));
		r = ft_join_no_strdup(r, code);
	}
	if (u_len == 0)
		r = build_color(WHITE_1, r, false);
	else
		r = build_color(WHITE_1, ft_join_strdup_left("~", r), false);
	r = ft_join_no_strdup(builded_username, r);
	return (r);
}
