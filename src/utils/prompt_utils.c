/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:02 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 16:55:09 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bf_prd(char *str, int d, char *color)
{
	char	*color_strdup;
	int		idx_str;
	int		idx;

	color_strdup = ft_strdup(color);
	idx_str = 0;
	write(1, color_strdup, ft_strlen(color));
	while (str[idx_str])
	{
		idx = 0;
		while (idx < d)
			idx++ ;
		write(1, &str[idx_str], 1);
		idx_str++ ;
	}
	write(1, NC, 7);
}

void	welcome_to_minishell(void)
{
	char	*users_c;

	users_c = YELLOW;
	bf_prd("\n\n\t>\t~ WELCOME TO MINISHELL ~", ANIME_TIME, ANIM_C);
	bf_prd("\n\t>", ANIME_TIME, ANIM_C);
	bf_prd("\n\t>\tMade by : ", ANIME_TIME, ANIM_C);
	bf_prd("\001\e[3m\001tboldrin\001\e[0m\002", ANIME_TIME, users_c);
	bf_prd(" && ", ANIME_TIME, ANIM_C);
	bf_prd("\001\e[3m\002rciaze\001\e[0m\002 ", ANIME_TIME, users_c);
	ft_printf(STDERR_FILENO, "\n\n\n");
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
	username = build_username_prompt(username);
	cwd = get_pwd();
	if (cwd == NULL)
		return (NULL);
	user_len = get_word_index(cwd, save_user);
	if (user_len == -1)
		user_len = 0;
	result = ft_join_strdup_left(cwd + user_len, build_color(GREEN, "]", 1));
	if (!result)
		return (malloc_failure(), NULL);
	result = ft_join_strdup_right(result, "\n");
	result = build_prompt(user_len, username, result);
	if (!result)
		return (malloc_failure(), NULL);
	return (result);
}
