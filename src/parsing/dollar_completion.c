/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/29 18:47:27 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// On regarde dans l'environnement si la variable existe,
// Si oui, on la remplace par sa valeur

char	*input_modif(char **spl_tab, int j, t_dollar *dollar, t_list **list)
{
	char	*str;

	str = ft_join_strdup(spl_tab[j], dollar->tmp_dup + dollar->end);
	free_d_array(spl_tab);
	if (!str)
		return (free_dollar(dollar), NULL);
	if (ft_strchr(str, '$')
		&& find_first_non_valid(ft_strchr(str, '$'), 1) != 1)
	{
		str = replace_dollar(' ', str, 0, list);
		if (!str)
			return (free_dollar(dollar), NULL);
	}
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
	if (!input)
		return (free_dollar(dollar), NULL);
	tmp = ft_substr(input, 0, start_of_search);
	if (!tmp)
		return (free_dollar(dollar), free(input), NULL);
	if (tmp[0])
	{
		if (!lst_add(list, &tmp, ' '))
			return (free_dollar(dollar), free(input), NULL);
	}
	split_tab = ft_split(input + start_of_search, ' ');
	if (!split_tab)
		return (free_dollar(dollar), free(input), NULL);
	j = d_t_case_loop(split_tab, input, dollar, list);
	if (j == -1)
		return (free_dollar(dollar), free(input), NULL);
	return (free(input), input_modif(split_tab, j, dollar, list));
}

int	set_dollar(t_dollar *dollar, char *content, int i, char what_case)
{
	int		len;

	dollar->tmp_dup = ft_strdup(content);
	free(content);
	if (!dollar->tmp_dup)
		return (0);
	dollar->start = ft_strchr(dollar->tmp_dup + i, '$') - dollar->tmp_dup;
	dollar->end = find_first_non_valid(dollar->tmp_dup, dollar->start + 1);
	if (dollar->tmp_dup[0] != '$' && dollar->end <= 0)
		dollar->end = ft_strlen(dollar->tmp_dup);
	len = dollar->end - dollar->start;
	dollar->env_var = check_env_variables(dollar->tmp_dup + dollar->start, len);
	if (!dollar->env_var)
		return (free(dollar->tmp_dup), 0);
	dollar->i = i;
	dollar->what_case = what_case;
	return (1);
}

int	replace_dollar_2(t_dollar *dollar, char **content, t_list **list)
{
	char		*tmp;

	tmp = ft_substr(dollar->tmp_dup, dollar->end,
			ft_strlen(dollar->tmp_dup) - dollar->end);
	if (!tmp)
		return (free_dollar(dollar), free(*content), 0);
	*content = ft_join(*content, tmp);
	if (!*content)
		return (free(dollar->tmp_dup), free(dollar->env_var), 0);
	if (ft_strchr(*content, '$')
		&& find_first_non_valid(ft_strchr(*content, '$'), 1) != 1)
	{
		*content = replace_dollar(dollar->what_case, *content, dollar->i, list);
		if (!*content)
			return (free_dollar(dollar), 0);
	}
	if (*content[0] == '\0')
		free_str(content);
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
		return (free_dollar(&dollar), malloc_failure(), NULL);
	if (what_case != DOUBLE_Q && ft_strchr(dollar.env_var, ' '))
		return (d_t_case(content, list, &dollar));
	if (dollar.env_var[0])
	{
		content = ft_join_strdup_right(content, dollar.env_var);
		if (!content)
			return (free_dollar(&dollar), malloc_failure(), NULL);
	}
	if (!replace_dollar_2(&dollar, &content, list))
		return (malloc_failure(), NULL);
	return (free_dollar(&dollar), content);
}
