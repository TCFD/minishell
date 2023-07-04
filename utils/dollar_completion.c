/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/04 11:50:14 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_env_variables(char *input)
{
	char		*value;
	char		*return_value;
	long int	end;

	end = ft_strchr(input, ' ') - (input);
	if (end <= 0)
		end = ft_strlen(input);
	value = ft_substr(input, 0, end);
	if (ft_strlen(value) != 1 && !ft_strncmp(value, "$?", ft_strlen(value)))
		return (free(value), ft_itoa(errno));
	return_value = ft_strdup(ft_getenv(value + 1));
	free (value);
	return (return_value);
}

void	expand(char **dest, int start, int if_case)
{
	char	*dup;
	char	*tmp;
	char	*dollar_pointer;
	char	*end;

	dup = ft_strdup(*dest);
	free(*dest);
	dollar_pointer = ft_strchr(dup + start, '$');
	end = NULL;
	if (if_case)
	{
		dollar_pointer = dup + start;
		tmp = ft_substr(dup, 0, start);
		space_end_case(&tmp, &end, DOUBLE_Q, NULL);
		free(tmp);
		*dest = ft_join(end, ft_substr(dup, start, ft_strlen(dup)));
		free(dup);
		return ;
	}
	*dest = ft_substr(dup, 0, dollar_pointer - dup);
	space_end_case(&dollar_pointer, &end, DOUBLE_Q, NULL);
	*dest = ft_join(*dest, end);
	free(dup);
}

char	*which_one_first(char *input)
{
	char	*dollar;
	char	*space;

	dollar = ft_strchr(input, '$');
	space = ft_strchr(input, ' ');
	if (dollar == space)
		return (input + ft_strlen(input));
	if ((dollar < space || !space) && dollar)
	{
		if (!dollar)
			return (input + ft_strlen(input));
		return (dollar);
	}
	if (!space)
		return (input + ft_strlen(input));
	return (space);
}

void	if_dollar(char **input, char **dest, char what_case, int i)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = ft_substr(*input, i, which_one_first(*input + i + 1) - *input - i);
	tmp = check_env_variables(tmp2);
	free(tmp2);
	*dest = ft_join(*dest, ft_substr(*input, 0, i));
	*dest = ft_join(*dest, tmp);
	tmp = which_one_first(*input + i + 1);
	if (ft_strchr(tmp, '$'))
		space_end_case(&tmp, dest, what_case, NULL);
	else if (tmp && what_case == DOUBLE_Q)
		*dest = ft_join(*dest, ft_strdup(tmp));
}

int	space_end_case(char **input, char **dest, char what_case, char *type)
{
	int			i;
	long int	end;

	i = 0;
	end = ft_strchr_rc(*input, what_case) - *input;
	if (end <= 0)
		end = ft_strlen(*input);
	if (what_case != DOUBLE_Q && *input)
	{
		if (ft_strnstr(*input, ">", ft_strlen(*input)))
			input[0] = find_chevrons(input, end);
		end = ft_strchr_rc(*input, ' ') - *input;
		if (end <= 0)
			end = ft_strlen(*input);
	}
	while (input[0][i] &&
		!(input[0][i] == '$' && input[0][i + 1] != ' ') && i < end)
		i++;
	if (input[0][i] == '$' && input[0][i + 1] != ' ')
		if_dollar(input, dest, what_case, i);
	else
		*dest = ft_join(*dest, ft_substr(*input, 0, end));
	if ((what_case == SPACE || what_case == NONE) && type)
		*type = INTERPRETABLE;
	return (end);
}
