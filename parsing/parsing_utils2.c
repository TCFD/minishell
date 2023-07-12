/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:27:47 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/12 16:38:42 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	which_one(char *input)
{
	char	*first_simple_quote;
	char	*first_double_quote;
	char	*first_space;

	first_simple_quote = ft_strchr_rc(input, '\'');
	first_double_quote = ft_strchr_rc(input, '\"');
	first_space = ft_strchr_rc(input, ' ');
	if (first_simple_quote == NULL)
		first_simple_quote = input + ft_strlen(input);
	if (first_double_quote == NULL)
		first_double_quote = input + ft_strlen(input);
	if (first_space == NULL)
		first_space = input + ft_strlen(input);
	if (first_space < first_double_quote && first_space < first_simple_quote)
		return (SPACE);
	if (first_simple_quote < first_double_quote)
		return (SIMPLE_Q);
	if (first_simple_quote > first_double_quote)
		return (DOUBLE_Q);
	return ('\0');
}

void	init_tabs(char char_tab[4], long int tab[4], char *input)
{
	char_tab[0] = '>';
	char_tab[1] = '<';
	char_tab[2] = ' ';
	char_tab[3] = '|';
	tab[0] = ft_strchr(input, char_tab[0]) - input;
	tab[1] = ft_strchr(input, char_tab[1]) - input;
	tab[2] = ft_strchr(input, char_tab[2]) - input;
	tab[3] = ft_strchr(input, char_tab[3]) - input;
}

void	lst_add(t_list **list, char **content, char type)
{
	(*list)->content = replace_dollar(*content);
	(*list)->type = type;
	(*list)->next = ft_lstnew("", NONE);
	(*list) = (*list)->next;
}

char	search_first_separator(char *input, int len)
{
	char		char_tab[4];
	long int	tab[4];
	long int	lowest;
	long int	y;
	int			i;

	init_tabs(char_tab, tab, input);
	lowest = len;
	i = -1;
	y = -1;
	while (++i < 4)
	{
		if (tab[i] < 0)
			tab[i] = len + 1;
		if (tab[i] <= lowest)
		{
			lowest = tab[i];
			y = i;
		}
	}
	i = y;
	if (i == -1)
		return (0);
	return (char_tab[i]);
}

void	set_separator(t_separators *sep, char *input)
{
	sep->what_case = which_one(input + sep->i);
	sep->separator = search_first_separator(input + sep->i,
			ft_strlen(input + sep->i));
	sep->w_string = ft_strchr(input + sep->i, sep->what_case)
		- (input + sep->i);
	sep->s_string = ft_strchr(input + sep->i, sep->separator)
		- (input + sep->i);
	if (sep->w_string < 0)
		sep->w_string = ft_strlen(input + sep->i);
	if (sep->s_string < 0)
		sep->s_string = ft_strlen(input + sep->i);
}
