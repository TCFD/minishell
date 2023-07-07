/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:35:02 by zbp15             #+#    #+#             */
/*   Updated: 2023/07/07 12:29:53 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Retourne soit "simple quote", "double quote", "space" ou "no quote", suivant ce qu'il y a en premier dans la string.

char which_one(char *input)
{
	char *first_simple_quote;
	char *first_double_quote;
	char *first_space;

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

void	init_tabs(char char_tab[4], long int tab[4], char * input)
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

char	search_first_separator(char *input)
{
	char		char_tab[4];
	long int	tab[4];
	long int	lowest;
	long int	y;
	int			i;
	int 		len;

	init_tabs(char_tab, tab, input);
	len = ft_strlen(input);
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

void	set_separator(t_separators *sep, char *input, int i)
{
	sep->what_case = which_one(input + i);
	sep->separator = search_first_separator(input + i);
	sep->w_string = ft_strchr(input + i, sep->what_case) - (input + i);
	sep->s_string = ft_strchr(input + i, sep->separator) - (input + i);
}

// avant chaque allocation dans liste(ou content), completion du $ par la valeur de la variable d'environnement

t_list	*all_tokens(char *input, t_list *list, int i)
{
	int		len;
	char	*content;
	char	tmp;
	t_separators sep;

	while (input[i] == SPACE)
		i += 1;
	len = ft_strlen(input);
	while (i < len)
	{
		set_separator(&sep, input, i);
		if (sep.w_string < 0)
			sep.w_string = ft_strlen(input + i);
		if (sep.s_string < 0)
			sep.s_string = ft_strlen(input + i);
		if (sep.s_string < sep.w_string)
		{	
			if (sep.s_string == 0 && input[i + 1 + sep.s_string] == input[i + sep.s_string])
				sep.s_string += 2;
			else if (sep.s_string == 0)
				sep.s_string += 1;
			content = ft_substr(input + i, 0, sep.s_string);
			i += ft_strlen(content);
			list->content = replace_dollar(content);
			list->type = NONE;
			list->next = ft_lstnew("", NONE);
			list = list->next;
		}
		else
		{
			if (sep.what_case == SIMPLE_Q || sep.what_case == DOUBLE_Q)
			{
				tmp = sep.what_case;
				if (input[i] == SIMPLE_Q || input[i] == DOUBLE_Q)
				{
					i++;
					content = ft_substr(input + i, 0, ft_strchr(input + i, sep.what_case) - (input + i));
					i += ft_strlen(content) + 1;
				}
				else
				{
					content = ft_substr(input + i, 0, ft_strchr(input + i, sep.what_case) - (input + i));
					i += ft_strlen(content);
				}
				if (input[i] != SPACE)
				{
					set_separator(&sep, input, i);
					if (sep.w_string < sep.s_string)
					{
						i++;
						content = ft_join(content, ft_substr(input + i, 0, ft_strchr(input + i, sep.what_case) - (input + i)));
						i += ft_strchr(input + i, sep.what_case) - (input + i) + 1;
					}
					else if (sep.w_string == sep.s_string)
					{
						content = ft_join(content, ft_substr(input + i, 0, ft_strlen(input + i)));
						i += ft_strlen(input + i);
					}
					set_separator(&sep, input, i);
					while ((sep.what_case != NONE || sep.what_case != SPACE) && sep.separator == SPACE && sep.s_string > 0)
					{
						if (sep.what_case == SIMPLE_Q || sep.what_case == DOUBLE_Q)
							i++;
						sep.w_string = ft_strchr(input + i, sep.what_case) - (input + i);
						if (sep.w_string < 0)
							sep.w_string = ft_strlen(input + i);
						content = ft_join(content, ft_substr(input + i, 0, sep.w_string));
						i += sep.w_string;
						if (sep.what_case == SIMPLE_Q || sep.what_case == DOUBLE_Q)
							i++;
						set_separator(&sep, input, i);
					}
				}
				list->content = replace_dollar(content);
				list->type = tmp;
				list->next = ft_lstnew("", NONE);
				list = list->next;
			}
			else
			{
				content = ft_substr(input + i, 0, sep.w_string);
				i += ft_strlen(content);
				list->content = replace_dollar(content);
				list->type = SPACE;
				list->next = ft_lstnew("", NONE);
				list = list->next;
			}
		}
		while (input[i] == SPACE)
			i += 1;
	}
	list = NULL;
	return (list);
}

t_list	*get_tokens(char *input)
{
	t_list	*list;
	t_list	*tmp;
	
	list = ft_lstnew("", '\0');
	tmp = list;
	all_tokens(input, tmp, 0);
	return (list);
}

void	parse_that_shit(char *tmp, t_cmd_and_opt *cmdopt)
{
	t_list	*list;
	t_list	*temp_list;
	char	*input;
	int		i;

	input = ft_strdup(tmp);
	list = get_tokens(input);
	temp_list = list;
	cmdopt->opt_ty_tb.tab = ft_calloc(ft_lstsize(list), sizeof(char *));
	cmdopt->opt_ty_tb.type = ft_calloc(ft_lstsize(list), sizeof(char));
	i = 0;
	while (temp_list->next)
	{
		cmdopt->opt_ty_tb.tab[i] = ft_strdup(temp_list->content);
		cmdopt->opt_ty_tb.type[i] = temp_list->type;
		temp_list = temp_list->next;
		i++;
	}
	cmdopt->opt_ty_tb.tab[i] = NULL;
	cmdopt->opt_ty_tb.type[i] = '\0';
	ft_lstclear(&list);
	free(input);
}
