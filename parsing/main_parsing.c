/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:35:02 by zbp15             #+#    #+#             */
/*   Updated: 2023/07/05 18:29:53 by rciaze           ###   ########.fr       */
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

// avant chaque allocation dans liste(ou content), completion du $ par la valeur de la variable d'environnement

void	all_tokens(char *input, t_list *list, int i)
{
	int		len;
	t_separators sep;
	char	*content;
	char	tmp;

	while (input[i] == SPACE)
		i += 1;
	len = ft_strlen(input);
	if (i == len)
		return ;
	while (i < len)
	{
		sep.what_case = which_one(input + i);
		sep.separator = search_first_separator(input + i);
		sep.w_string = ft_strchr(input + i, sep.what_case) - (input + i);
		sep.s_string = ft_strchr(input + i, sep.separator) - (input + i);
		if (sep.w_string < 0)
			sep.w_string = ft_strlen(input + i);
		if (sep.s_string < 0)
			sep.s_string = ft_strlen(input + i);
		if (sep.s_string < sep.w_string)
		{	
			if (sep.s_string == 0)
				sep.s_string += 1;
			list->next = ft_lstnew(ft_substr(input + i, 0, sep.s_string), NONE);
			list = list->next;
			i += ft_strlen(list->content);
		}
		else
		{
			if (sep.what_case == SIMPLE_Q || sep.what_case == DOUBLE_Q)
			{
				tmp = sep.what_case;
				i++;
				content = ft_substr(input + i, 0, ft_strchr(input + i, sep.what_case) - (input + i));
				i += ft_strlen(content) + 1;
				if (input[i] != SPACE)
				{
					sep.what_case = which_one(input + i);
					sep.separator = search_first_separator(input + i);
					while (sep.what_case > sep.separator)
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
						sep.what_case = which_one(input + i);
					}
				}
				list->next = ft_lstnew(strdup(content), tmp);
				free(content);
				list = list->next;
			}
			else
			{
				list->next = ft_lstnew(ft_substr(input + i, 0, sep.w_string), SPACE);
				list = list->next;
				i += ft_strlen(list->content);
			}
		}
		while (input[i] == SPACE)
			i += 1;
	}
}

t_list	*get_tokens(char *input)
{
	char	what_case;
	t_list	*list;
	t_list	*tmp;
	
	what_case = which_one(input);
	if (what_case == DOUBLE_Q || what_case == SIMPLE_Q)
		list = ft_lstnew(ft_substr(input, 1, ft_strchr(input + 1, what_case) - input - 1), what_case);
	else
		list = ft_lstnew(ft_substr(input, 0, ft_strchr(input, what_case) - input), what_case);
	tmp = list;
	if (what_case == DOUBLE_Q || what_case == SIMPLE_Q)
		all_tokens(input, tmp, ft_strlen(tmp->content) + 2);
	else
		all_tokens(input, tmp, ft_strlen(tmp->content));	
	return (list);
}

void	parse_that_shit(char *tmp, t_cmd_and_opt *cmdopt)
{
	t_list	*list;
	t_list	*temp_list;
	char	*input;
	int		i;

	input = ft_strdup(tmp);
	while (*input == SPACE)
		input += 1;	
	list = get_tokens(input);
	temp_list = list;
	cmdopt->opt_and_type_tab.tab = ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
	cmdopt->opt_and_type_tab.type = ft_calloc(ft_lstsize(list) + 1, sizeof(char));
	i = 0;
	while (temp_list)
	{
		cmdopt->opt_and_type_tab.tab[i] = ft_strdup(temp_list->content);
		cmdopt->opt_and_type_tab.type[i] = temp_list->type;
		temp_list = temp_list->next;
		i++;
	}
	cmdopt->opt_and_type_tab.tab[i] = NULL;
	cmdopt->opt_and_type_tab.type[i] = '\0';
	ft_lstclear(&list);
	free(input);
}
