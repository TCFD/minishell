/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:02 by wolf              #+#    #+#             */
/*   Updated: 2023/06/19 15:26:44 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bf_prd(char *str, int d, char *color)
{
	char	*str_cara;
	char	*color_strdup;
	int		idx_str;
	int		idx;

	color_strdup = ft_strdup(color);
	idx_str = 0;
	write(1, color_strdup, ft_strlen(color));
	free(color_strdup);
	while (str[idx_str])
	{
		idx = 0;
		while (idx < d)
			idx++ ;
		str_cara = (char*)malloc(2 * sizeof(char));
		str_cara[0] = str[idx_str];
		str_cara[1] = '\0';
		write(1, str_cara, 1);
		free(str_cara);
		idx_str++ ;
	}
	color_strdup = ft_strdup("\033[0m");
	write(1, color_strdup, ft_strlen(color_strdup));
	free(color_strdup);
}

void	welcome_to_minishell(void)
{
	int		dl;

	dl = 10000;
	bf_prd("\n\n\t\t>     ~ WELCOME TO MINISHELL ~", dl, GREEN);
	bf_prd("\n\t\t>", dl, GREEN);
	bf_prd("\n\t\t>   Made by : tboldrin && rciaze", dl, GREEN);
	ft_printf("\n\n\n");
}

char	*ccn(char *str, char *color)
{
	ft_printf("%s%s%s\n", color, str, NC);
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
