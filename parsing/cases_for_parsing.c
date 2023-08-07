/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_for_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:23:14 by rciaze            #+#    #+#             */
/*   Updated: 2023/08/07 19:05:40 by zbp15            ###   ########.fr       */
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
		*content = replace_dollar(*content, 0);
	lst_add(list, content, NONE);
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
	}
	if (sep->what_case != '\'' || (sep->what_case == '\'' && sep->w_string > 0))
		*content = replace_dollar(*content, 0);
	if (input[sep->i] != SPACE && input[sep->i])
		case_4_or_5(sep, content, input);
	lst_add(list, content, sep->tmp);
}

void	case_4_or_5(t_separators *sep, char **content, char *s1)
{
	sep->tmp_i = ft_strlen(*content);
	set_separator(sep, s1);
	if (sep->w_string < sep->s_string)
	{
		sep->i += 1;
		*content = ft_join(*content, ft_substr(s1 + sep->i, 0,
					ft_strchr(s1 + sep->i, sep->what_case) - (s1 + sep->i)));
		sep->i += ft_strchr(s1 + sep->i, sep->what_case)
			- (s1 + sep->i) + 1;
	}
	else if (sep->what_case == SPACE && sep->separator == SPACE)
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
			*content = replace_dollar(*content, sep->tmp_i);
	case_4_5_part_2(sep, content, s1);
}

void	case_4_5_part_2(t_separators *sep, char **content, char *input)
{
	set_separator(sep, input);
	while ((sep->separator == SPACE || sep->separator == NONE)
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
			*content = replace_dollar(*content, sep->tmp_i);
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
		*content = replace_dollar(*content, 0);
	lst_add(list, content, SPACE);
}
