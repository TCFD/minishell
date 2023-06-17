/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:02 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 14:42:20 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ccn(char *str, char *color)
{
	ft_printf("%s%s%s ", color, str, NC);
	return (str);
}

char	*stick_color(char *str, char *color)
{
	char	*new_str;

	new_str = ft_join(color, str);
	new_str = ft_join(new_str, ft_strdup(NC));
	return (new_str);
}

char	*display_user_prompt(void)
{
	char	*result;
	char	*user;
	char	cwd[1024];

	if (!(user = getenv("USER")))
		return (NULL);
	user = stick_color(ft_join(ft_strdup(user), ft_strdup("@minishell42:")), ft_strdup("\033[32;1m"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	result = ft_join(ft_strdup(cwd + ft_len(user) + 5), ft_strdup(" $ "));
	result = stick_color(ft_join(ft_strdup(" ~"), result), ft_strdup(BLUE));
	result = ft_join(user, result);
	return (result);
}
