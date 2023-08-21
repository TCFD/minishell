/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/08/15 14:31:04 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Regarde dans l'environement si la variable existe,
// si oui, la remplace par sa valeur

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
	if (!ft_strncmp(value, "$?", ft_strlen(value)))
		return (free(value), ft_itoa(error_code));
	return_value = ft_strdup(ft_getenv(value + 1));
	free(value);
	return (return_value);
}

char	*d_t_case(char *input, t_list **list, t_dollar *dollar)
{
	int		start_of_search;
	char	**split_tab;
	char 	*tmp;
	int 	j;

	start_of_search = ft_strchr(dollar->env_var, ' ') - dollar->env_var + ft_strlen(input);
	input = ft_join(input, ft_strdup(dollar->env_var));
	tmp = ft_substr(input, 0, start_of_search);
	if (tmp[0])
		lst_add(list, &tmp, ' ');
	split_tab = ft_split(input + start_of_search, ' ');
	j = -1;
	while(split_tab[++j + 1])
	{
		tmp = ft_strdup(split_tab[j]);
		lst_add(list, &tmp, ' ');
	}
	free(input);
	input = ft_join(ft_strdup(split_tab[j]), ft_strdup(dollar->tmp_dup + dollar->end));
	free_d_array(split_tab);
	if (ft_strchr(input, '$') && find_first_non_valid(ft_strchr(input, '$'), 1) != 1)
		input = replace_dollar(' ', input, 0, list);
	return (input);
}

char	*replace_dollar(char what_case, char *input, int i, t_list **list)
{
	t_dollar	dollar;

	if (input[i] != '$' && !ft_strchr(input + i, '$'))
		return (input);
	dollar.tmp_dup = ft_strdup(input);
	free(input);
	dollar.start = ft_strchr(dollar.tmp_dup + i, '$') - dollar.tmp_dup;
	dollar.end = find_first_non_valid(dollar.tmp_dup, dollar.start + 1);
	if (dollar.tmp_dup[0] != '$' && dollar.end <= 0)
		dollar.end = ft_strlen(dollar.tmp_dup);
	dollar.env_var = check_env_variables(dollar.tmp_dup + dollar.start, dollar.end - dollar.start);
	input = ft_substr(dollar.tmp_dup, 0, dollar.start);
	if (what_case != DOUBLE_Q && ft_strchr(dollar.env_var, ' '))
		return (d_t_case(input, list, &dollar));
	if (dollar.env_var[0])
		input = ft_join(input, ft_strdup(dollar.env_var));
	input = ft_join(input, ft_substr(dollar.tmp_dup, dollar.end, ft_strlen(dollar.tmp_dup) - dollar.end));
	if (ft_strchr(input, '$') && find_first_non_valid(ft_strchr(input, '$'), 1) != 1)
		input = replace_dollar(what_case, input, i, list);
	if (!input[0])
	{
		free(input);
		input = NULL;
	}
	return (free(dollar.tmp_dup), free(dollar.env_var), input);
}
