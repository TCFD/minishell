/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_for_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:23:14 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/29 14:56:33 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	case_1(t_separators *sep, char **content, char *input, t_list **list)
{
	if (sep->s_string == 0 && input[sep->i + 1] == input[sep->i])
		sep->s_string += 2;
	else if (sep->s_string == 0)
		sep->s_string += 1;
	*content = ft_substr(input + sep->i, 0, sep->s_string);
	if (!(*content))
		return (0);
	sep->i += ft_strlen(*content);
	if (sep->what_case != '\'')
		*content = replace_dollar(sep->what_case, *content, 0, list);
	if (*content)
	{
		if (!lst_add(list, content, SPACE))
			return (0);
	}
	return (1);
}

int	case_2_or_3(t_separators *sep, char **content, char *input,
	t_list **list)
{
	sep->tmp = sep->what_case;
	if (input[sep->i] == SIMPLE_Q || input[sep->i] == DOUBLE_Q)
		case_2(sep, content, input);
	else
		case_3(sep, content, input);
	if (!(*content))
		return (0);
	if (sep->what_case != '\'' || (sep->what_case == '\'' && sep->w_string > 0))
		*content = replace_dollar(sep->what_case, *content, 0, list);
	if (!check_if_ifs(input[sep->i]) && input[sep->i])
	{
		if (!case_4_or_5(sep, content, input, list))
			return (0);
	}
	if (*content)
	{
		if (!lst_add(list, content, sep->what_case))
			return (0);
	}
	return (1);
}

int	case_4_or_5(t_separators *sep, char **content, char *s1, t_list **list)
{
	sep->tmp_i = ft_strlen(*content);
	set_separator(sep, s1);
	if ((sep->w_string < sep->s_string) || check_if_ifs(sep->separator))
		case_4(sep, content, s1);
	else if (sep->w_string == sep->s_string)
		case_5(sep, content, s1);
	if (!(*content))
		return (0);
	if (sep->what_case != '\'' || (sep->what_case == '\'' && sep->w_string > 0))
		*content = replace_dollar(sep->what_case, *content, 0, list);
	if (s1[sep->i] && !check_if_ifs(s1[sep->i]))
		case_4_5_part_2(sep, content, s1, list);
	return (1);
}

int	case_4_5_part_2(t_separators *sep, char **ct,
	char *input, t_list **list)
{
	set_separator(sep, input);
	while ((check_if_ifs(sep->separator) || sep->separator == NONE)
		&& sep->s_string > 0)
	{
		if (what_case_equal_c(sep->what_case, input[sep->i]))
		{
			sep->i += 1;
			sep->in_quote = true;
		}
		if (!input[sep->i])
			break ;
		sep->w_string = ft_strchr(input + sep->i, sep->what_case)
			- (input + sep->i);
		if (sep->w_string < 0)
			sep->w_string = ft_strlen(input + sep->i);
		sep->tmp_i = ft_strlen(*ct);
		if (!i_dont_like_norme(ct, sep, input, list))
			return (0);
		sep->i += sep->w_string;
		if (what_case_equal_c(sep->what_case, input[sep->i]) && sep->in_quote)
			sep->i += 1;
		set_separator(sep, input);
	}
	return (1);
}

int	final_case(t_separators *sep, char **content, char *input,
	t_list **list)
{
	*content = ft_substr(input + sep->i, 0, sep->w_string);
	if (!(*content))
		return (0);
	sep->i += ft_strlen(*content);
	if (sep->what_case != '\'')
		*content = replace_dollar(sep->what_case, *content, 0, list);
	if (*content)
	{
		if (!lst_add(list, content, SPACE))
			return (0);
	}
	return (1);
}
