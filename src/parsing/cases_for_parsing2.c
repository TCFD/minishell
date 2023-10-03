/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_for_parsing2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:31:27 by rciaze            #+#    #+#             */
/*   Updated: 2023/10/03 21:35:50 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_2(t_separators *sep, char **content, char *input)
{
	sep->i += 1;
	*content = ft_substr_protect(input + sep->i, 0,
			ft_strchr(input + sep->i, sep->what_case) - (input + sep->i));
	sep->i += ft_strlen(*content) + 1;
}

void	case_3(t_separators *sep, char **content, char *input)
{
	*content = ft_substr_protect(input + sep->i, 0,
			ft_strchr(input + sep->i, sep->what_case) - (input + sep->i));
	sep->i += ft_strlen(*content);
	if (content[0][ft_strlen(*content) - 1] == '$'
		&& input[sep->i] == sep->what_case)
		content[0][ft_strlen(*content) - 1] = '\0';
	sep->what_case = 0;
}

void	case_4(t_separators *sep, char **content, char *s1)
{
	if (what_case_equal_c(sep->what_case, s1[sep->i]))
	{
		sep->i += 1;
		sep->in_quote = true;
	}
	*content = ft_join(*content, ft_substr_protect(s1 + sep->i, 0,
				ft_strchr(s1 + sep->i, sep->what_case) - (s1 + sep->i)));
	sep->i += ft_strchr(s1 + sep->i, sep->what_case) - (s1 + sep->i);
	if (what_case_equal_c(sep->what_case, s1[sep->i]) && sep->in_quote)
		sep->i += 1;
}

void	case_5(t_separators *sep, char **content, char *s1)
{
	*content = ft_join(*content, ft_substr_protect(s1 + sep->i, 0,
				ft_strlen(s1 + sep->i)));
	sep->i += ft_strlen(s1 + sep->i);
}

int	i_dont_like_norme(char **ct, t_separators *sep, char *input, t_list **list)
{
	char	*tmp;

	tmp = ft_substr_protect(input + sep->i, 0, sep->w_string);
	if (!tmp)
		return (0);
	if (tmp[ft_strlen(tmp) - 1] == '$'
		&& input[sep->i + ft_strlen(tmp)] == sep->what_case)
		tmp[ft_strlen(tmp) - 1] = '\0';
	*ct = ft_join(*ct, tmp);
	if (!(*ct))
		return (0);
	if (sep->what_case != SIMPLE_Q)
		*ct = replace_dollar(sep->what_case, *ct, sep->tmp_i, list);
	return (1);
}
