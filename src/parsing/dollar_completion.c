/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/10/04 17:13:42 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// On regarde dans l'environnement si la variable existe,
// Si oui, on la remplace par sa valeur

char	*input_modif(char **spl_tab, int j, t_dollar *dollar, t_list **list)
{
	char	*str;

	str = ft_join_strdup(spl_tab[j], dollar->tmp_dup + dollar->end);
	if (ft_strchr(str, '$')
		&& find_first_non_valid(ft_strchr(str, '$'), 1) != 1)
		str = replace_dollar(' ', str, 0, list);
	return (str);
}

char	*d_t_case(char *input, t_list **list, t_dollar *dollar)
{
	int		start_of_search;
	char	**split_tab;
	char	*tmp;
	int		j;

	start_of_search = (ft_strchr(dollar->env_var, ' ') - dollar->env_var
			+ ft_strlen(input));
	input = ft_join_strdup_right(input, dollar->env_var);
	tmp = ft_substr(input, 0, start_of_search);
	if (tmp[0])
		lst_add(list, &tmp, ' ');
	split_tab = ft_split(input + start_of_search, ' ');
	j = d_t_case_loop(split_tab, list);
	return (input_modif(split_tab, j, dollar, list));
}

int	set_dollar(t_dollar *dollar, char *content, int i, char what_case)
{
	int		len;

	dollar->tmp_dup = ft_strdup(content);
	if (!dollar->tmp_dup)
		return (0);
	dollar->start = ft_strchr(dollar->tmp_dup + i, '$') - dollar->tmp_dup;
	dollar->end = find_first_non_valid(dollar->tmp_dup, dollar->start + 1);
	if (dollar->tmp_dup[0] != '$' && dollar->end <= 0)
		dollar->end = ft_strlen(dollar->tmp_dup);
	len = dollar->end - dollar->start;
	dollar->env_var = check_env_variables(dollar->tmp_dup + dollar->start, len);
	if (!dollar->env_var)
		return (0);
	dollar->i = i;
	dollar->what_case = what_case;
	return (1);
}

int	replace_dollar_2(t_dollar *dollar, char **content, t_list **list)
{
	char		*tmp;

	tmp = ft_substr(dollar->tmp_dup, dollar->end,
			ft_strlen(dollar->tmp_dup) - dollar->end);
	*content = ft_join_no_strdup(*content, tmp);
	if (ft_strchr(*content, '$')
		&& find_first_non_valid(ft_strchr(*content, '$'), 1) != 1)
		*content = replace_dollar(dollar->what_case, *content, dollar->i, list);
	return (1);
}

char	*replace_dollar(char what_case, char *content, int i, t_list **list)
{
	t_dollar	dollar;

	if (content[i] != '$' && !ft_strchr(content + i, '$'))
		return (content);
	if (!set_dollar(&dollar, content, i, what_case))
		return (malloc_failure(), NULL);
	content = ft_substr(dollar.tmp_dup, 0, dollar.start);
	if (!content)
		return (malloc_failure(), NULL);
	if (what_case != DOUBLE_Q && ft_strchr(dollar.env_var, ' '))
		return (d_t_case(content, list, &dollar));
	if (dollar.env_var[0])
		content = ft_join_strdup_right(content, dollar.env_var);
	if (!replace_dollar_2(&dollar, &content, list))
		return (malloc_failure(), NULL);
	return (content);
}
