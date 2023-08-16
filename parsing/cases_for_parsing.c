/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_for_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:23:14 by rciaze            #+#    #+#             */
/*   Updated: 2023/08/16 20:07:05 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_1(t_separators *sep, char **content, char *input, t_list **list)
{
	if (sep->s_string == 0 && input[sep->i + 1 + sep->s_string]
		== input[sep->i + sep->s_string])
		sep->s_string += 2;
	else if (sep->s_string == 0)
		sep->s_string += 1;
	*content = ft_substr(input + sep->i, 0, sep->s_string);
	sep->i += ft_strlen(*content);
	if (sep->what_case != '\'')
		*content = replace_dollar(sep->what_case, *content, 0, list);
	if (*content)
		lst_add(list, content, SPACE);
}

void	case_2_or_3(t_separators *sep, char **content, char *input,
	t_list **list)
{
	sep->tmp = sep->what_case;
	if (input[sep->i] == SIMPLE_Q || input[sep->i] == DOUBLE_Q)
	{
		sep->i += 1;
		*content = ft_substr(input + sep->i, 0,
				ft_strchr(input + sep->i, sep->what_case) - (input + sep->i));
		sep->i += ft_strlen(*content) + 1;
	}
	else
	{
		*content = ft_substr(input + sep->i, 0,
				ft_strchr(input + sep->i, sep->what_case) - (input + sep->i));
		sep->i += ft_strlen(*content);
		sep->what_case = 0;
	}
	if (sep->what_case != '\'' || (sep->what_case == '\'' && sep->w_string > 0))
		*content = replace_dollar(sep->what_case, *content, 0, list);
	if (!check_if_IFS(input[sep->i]) && input[sep->i])
		case_4_or_5(sep, content, input, list);
	if (*content)
		lst_add(list, content, sep->what_case);
}

void	case_4_or_5(t_separators *sep, char **content, char *s1, t_list **list)
{
	sep->tmp_i = ft_strlen(*content);
	set_separator(sep, s1);
	if (sep->w_string < sep->s_string)
	{
		if ((sep->what_case == SIMPLE_Q && s1[sep->i] == SIMPLE_Q)
			|| (sep->what_case == DOUBLE_Q && s1[sep->i] == DOUBLE_Q))
			sep->i += 1;
		*content = ft_join(*content, ft_substr(s1 + sep->i, 0,
					ft_strchr(s1 + sep->i, sep->what_case) - (s1 + sep->i)));
		sep->i += ft_strchr(s1 + sep->i, sep->what_case)
			- (s1 + sep->i) + 1;
	}
	else if (check_if_IFS(sep->separator) && check_if_IFS(sep->separator))
	{
		*content = ft_join(*content, ft_substr(s1 + sep->i, 0,
					ft_strchr(s1 + sep->i, sep->what_case) - (s1 + sep->i)));
		sep->i += ft_strchr(s1 + sep->i, sep->what_case) - (s1 + sep->i) + 1;
	}
	else if (sep->w_string == sep->s_string)
	{
		*content = ft_join(*content, ft_substr(s1 + sep->i, 0,
					ft_strlen(s1 + sep->i)));
		sep->i += ft_strlen(s1 + sep->i);
	}
	if (sep->what_case != '\'' || (sep->what_case == '\'' && sep->w_string > 0))
		*content = replace_dollar(sep->what_case, *content, sep->tmp_i, list);
	if (s1[sep->i])
		case_4_5_part_2(sep, content, s1, list);
}

void	case_4_5_part_2(t_separators *sep, char **content, char *input, t_list **list)
{
	set_separator(sep, input);
	while ((check_if_IFS(sep->separator) || sep->separator == NONE)
		&& sep->s_string > 0)
	{
		if ((sep->what_case == SIMPLE_Q && input[sep->i] == SIMPLE_Q)
			|| (sep->what_case == DOUBLE_Q && input[sep->i] == DOUBLE_Q))
			sep->i += 1;
		if (!input[sep->i])
			break ;
		sep->w_string = ft_strchr(input + sep->i, sep->what_case)
			- (input + sep->i);
		if (sep->w_string < 0)
			sep->w_string = ft_strlen(input + sep->i);
		sep->tmp_i = ft_strlen(*content);
		*content = ft_join(*content,
				ft_substr(input + sep->i, 0, sep->w_string));
		if (sep->what_case != '\'' || (sep->what_case == '\''
				&& sep->w_string > 0))
			*content = replace_dollar(sep->what_case, *content, sep->tmp_i, list);
		sep->i += sep->w_string;
		if (sep->what_case == SIMPLE_Q || sep->what_case == DOUBLE_Q)
			sep->i += 1;
		set_separator(sep, input);
	}
}

void	final_case(t_separators *sep, char **content, char *input,
	t_list **list)
{
	*content = ft_substr(input + sep->i, 0, sep->w_string);
	sep->i += ft_strlen(*content);
	if (sep->what_case != '\'')
		*content = replace_dollar(sep->what_case, *content, 0, list);
	if (*content)
		lst_add(list, content, SPACE);
}
