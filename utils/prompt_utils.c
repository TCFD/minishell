/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:02 by wolf              #+#    #+#             */
/*   Updated: 2023/06/27 16:34:22 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		str_cara = malloc(2 * sizeof(char));
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

	dl = 10000000;
	bf_prd("\n\n\t\t>     ~ WELCOME TO MINISHELL ~", dl, GREEN);
	bf_prd("\n\t\t>", dl, GREEN);
	bf_prd("\n\t\t>   Made by : tboldrin && rciaze", dl, GREEN);
	ft_printf("\n\n\n");
}

char	*stick_color(char *str, char *color)
{
	char	*new_str;

	new_str = ft_join(color, str);
	new_str = ft_join(new_str, ft_strdup(NC));
	return (new_str);
}

int	get_word_index(char const *str, char const *word)
{
	int	idx;
	int	word_idx;

	idx = 0;
	while (str[idx])
	{
		word_idx = 1;
		if (str[idx] == word[0])
		{
			while (str[idx + word_idx] == word[word_idx])
				word_idx++ ;
			if (word_idx == (int)ft_strlen(word))
				return (idx + word_idx);
			idx += word_idx;
		}
		idx++ ;
	}
	return (-1);
}

char	*display_user_prompt(char *username)
{
	char	*save_user;
	char	*result;
	char	cwd[1024];
	int		user_len;

	save_user = username;
	username = stick_color(ft_join(ft_strdup(username),
				ft_strdup("@minishell42:")), ft_strdup("\033[32;1m"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	user_len = get_word_index(cwd, save_user);
	result = ft_join(ft_strdup(cwd + user_len), ft_strdup(" $ "));
	result = stick_color(ft_join(ft_strdup(" ~"), result), ft_strdup(BLUE));
	result = ft_join(username, result);
	return (result);
}
