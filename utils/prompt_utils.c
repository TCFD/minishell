/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:02 by wolf              #+#    #+#             */
/*   Updated: 2023/09/10 16:50:45 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bf_prd(char *str, int d, char *color)
{
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
		write(1, &str[idx_str], 1);
		idx_str++ ;
	}
	write(1, "\033[0m", 5);
}

void	welcome_to_minishell(void)
{
	int		dl;

	dl = 75000000;
	bf_prd("\n\n\t\t>\t~ WELCOME TO MINISHELL ~", dl, GREEN);
	bf_prd("\n\t\t>", dl, GREEN);
	bf_prd("\n\t\t>\tMade by : tboldrin && rciaze ", dl, GREEN);
	ft_printf("\n\n\n");
}

char	*stick_color(char *str, char *color)
{
	char	*new_str;

	new_str = ft_join(color, str);
	new_str = ft_join(new_str, ft_strdup(NC));
	return (new_str);
}

int	get_word_index(char *str, char const *word)
{
	int	idx;
	int	word_idx;

	idx = 0;
	while (str[idx])
	{
		word_idx = 0;
		if (str[idx] == word[0])
		{
			while (str[idx + word_idx]
				&& str[idx + word_idx] == word[word_idx])
				word_idx++ ;
			if (word_idx == (int)ft_strlen(word))
				return (idx + word_idx);
			if (word_idx > (int)ft_strlen(word))
				return ((int)ft_strlen(str));
			idx += word_idx;
		}
		if (idx == (int)ft_strlen(str))
			break ;
		idx++ ;
	}
	return (-1);
}

char	*display_user_prompt(char *username)
{
	char	*save_user;
	char	*result;
	char	*cwd;
	int		user_len;

	save_user = username;
	username = stick_color(ft_join(ft_strdup(username),
				ft_strdup("@minishell42:")), ft_strdup("\033[32;1m"));
	cwd = get_pwd();
	if (cwd == NULL)
		return (free(username), NULL);
	user_len = get_word_index(cwd, save_user);
	if (user_len == -1)
		user_len = 0;
	result = ft_join(ft_strdup(cwd + user_len), ft_strdup(" $ "));
	if (user_len == 0)
		result = stick_color(ft_join(ft_strdup(" "), result), ft_strdup(BLUE));
	else
		result = stick_color(ft_join(ft_strdup(" ~"), result), ft_strdup(BLUE));
	if (g_error_code == 0 || get_last_sign() == 130)
		username = ft_join(ft_strdup("🤌 "), username);
	else
		username = ft_join(ft_strdup("🖕 "), username);
	result = ft_join(username, result);
	return (free(cwd), result);
}
