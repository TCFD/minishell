/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/28 18:41:29 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// On regarde dans l'environnement si la variable existe,
// Si oui, on la remplace par sa valeur

int	find_first_non_valid(char *input, int i)
{
	if (input[i] <= '9' && input[i] >= '0')
		return (i + 1);
	if (input[i] == '?')
		return (i + 1);
	while (input[i])
	{
		if (ft_isalnum(input[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

char	*check_env_variables(char *input, int end)
{
	char		*value;
	char		*return_value;
	int			start;

	start = 0;
	if (end == 1)
		return (ft_strdup("$"));
	value = ft_substr(input, start, end - start);
	if (!value)
		return (NULL);
	if (!ft_strncmp(value, "$?", ft_strlen(value)))
		return (free(value), ft_itoa(g_error_code));
	return_value = ft_strdup(ft_getenv(value + 1));
	free(value);
	return (return_value);
}

char	*input_modif(char **spl_tab, int j, t_dollar *dollar, t_list **list)
{
	char	*str;

	str = ft_join(ft_strdup(spl_tab[j]),
			ft_strdup(dollar->tmp_dup + dollar->end));
	free_d_array(spl_tab);
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
	input = ft_join(input, ft_strdup(dollar->env_var));
	tmp = ft_substr(input, 0, start_of_search);
	if (tmp[0])
		lst_add(list, &tmp, ' ');
	split_tab = ft_split(input + start_of_search, ' ');
	j = -1;
	while (split_tab[++j + 1])
	{
		tmp = ft_strdup(split_tab[j]);
		lst_add(list, &tmp, ' ');
	}
	free(input);
	return (input_modif(split_tab, j, dollar, list));
}

int	set_dollar(t_dollar *dollar, char *content, int i)
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
	return (1);
}

char	*replace_dollar(char what_case, char *content, int i, t_list **list)
{
	t_dollar	dollar;

	if (content[i] != '$' && !ft_strchr(content + i, '$'))
		return (content);
	if (!set_dollar(&dollar, content, i))
		return (NULL);
	content = ft_substr(dollar.tmp_dup, 0, dollar.start);
	if (!content)
		return (free(dollar.tmp_dup), free(dollar.env_var), NULL);
	if (what_case != DOUBLE_Q && ft_strchr(dollar.env_var, ' '))
		return (d_t_case(content, list, &dollar));
	if (dollar.env_var[0])
	{
		content = ft_join_strdup_right(content, dollar.env_var);
		if (!content)
			return (free(dollar.tmp_dup), free(dollar.env_var), NULL);
	}
	content = ft_join(content, ft_substr(dollar.tmp_dup, dollar.end, ft_strlen(dollar.tmp_dup) - dollar.end));
	if (!content)
			return (free(dollar.tmp_dup), free(dollar.env_var), NULL);
	if (ft_strchr(content, '$')
		&& find_first_non_valid(ft_strchr(content, '$'), 1) != 1)
		content = replace_dollar(what_case, content, i, list);
	if (!content && content[0] == '\0')
		free_str(&content);
	return (free(dollar.tmp_dup), free(dollar.env_var), content);
}
