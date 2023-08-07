/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/08/07 19:12:14 by zbp15            ###   ########.fr       */
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

char	*check_env_variables(char *input, int start, int end)
{
	char		*value;
	char		*return_value;

	if (end == 1)
		return (ft_strdup("$"));
	value = ft_substr(input, start, end - start);
	if (!ft_strncmp(value, "$?", ft_strlen(value)))
		return (free(value), ft_itoa(error_code));
	return_value = ft_strdup(ft_getenv(value + 1));
	free (value);
	return (return_value);
}

char	*replace_dollar(char *input, int i)
{
	char	*tmp_dup;
	int		start;
	int		end;

	if (input[i] != '$' && !ft_strchr(input + i, '$'))
		return (input);
	tmp_dup = ft_strdup(input);
	free(input);
	start = ft_strchr(tmp_dup + i, '$') - tmp_dup;
	end = find_first_non_valid(tmp_dup, start + 1);
	if (tmp_dup[0] != '$' && end <= 0)
		end = ft_strlen(tmp_dup);
	input = ft_substr(tmp_dup, 0, start);
	input = ft_join(input, check_env_variables(tmp_dup, start, end));
	input = ft_join(input, ft_substr(tmp_dup, end, ft_strlen(tmp_dup) - end));
	if (ft_strchr(input + 1, '$'))
		input = replace_dollar(input, i);
	return (input);
}
