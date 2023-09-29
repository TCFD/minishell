/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:25:31 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/28 20:34:45 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	d_t_case_loop(char **split_tab, char *input,
	t_dollar *dollar, t_list **list)
{
	int		j;
	char	*tmp;

	j = -1;
	while (split_tab[++j + 1])
	{
		tmp = ft_strdup(split_tab[j]);
		if (!tmp)
			return (free_dollar(dollar), free(input), -1);
		if (!lst_add(list, &tmp, ' '))
			return (free_dollar(dollar), free(input), -1);
	}
	return (j);
}
