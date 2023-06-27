/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/27 11:35:50 by zbp15            ###   ########.fr       */
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
	if (!ft_strncmp(value, "$?", ft_strlen(value)))
		return (free(value), ft_itoa(errno));
	return_value = ft_strdup(getenv(value + 1));
	free (value);
	return (return_value);
}

void	expand(char **dest)
{
	char	*dup;
	char	*dollar_pointer;
	char	*end;

	dup = ft_strdup(*dest);
	free(*dest);
	*dest = ft_substr(dup, 0, ft_strchr(dup, '$') - dup);
	dollar_pointer = ft_strchr(dup, '$');
	end = NULL;
	space_end_case(&dollar_pointer, &end, DOUBLE_Q);
	*dest = ft_join(*dest, end);
	free(dup);
}

char *	which_one_first(char *input)
{
	char	*dollar;
	char	*space;

	dollar = ft_strchr(input, '$');
	space = ft_strchr(input, ' ');
	if (dollar == space)
		return (input + ft_strlen(input));
	if (dollar > space)
	{
		if (dollar == input)
			return (input + ft_strlen(input));
		return (dollar);
	}
	if (space == input)
			return (input + ft_strlen(input));
	return (space);
}

int	space_end_case(char **input, char **dest, char what_case)
{
	int			i;
	char		*tmp;
	char		*tmp2;
	long int	end;

	i = 0;
	end = ft_strchr_rc(*input, what_case) - *input;
	if (end <= 0)
		end = ft_strlen(*input);
	while (input[0][i] && !(input[0][i] == '$' && input[0][i + 1] != ' ') && i < end)
		i++;
	if (input[0][i] == '$' && input[0][i + 1] != ' ')
	{
		tmp2 = ft_substr(*input, i, which_one_first(*input + 1) - *input);
		printf("dest = %s\n\n", tmp2);
		tmp = check_env_variables(tmp2);
		free(tmp2);
		*dest = (ft_join(*dest, ft_substr(*input, 0, i)));
		*dest = (ft_join(*dest, ft_strdup(tmp)));
		tmp = which_one_first(*input + i + 1);
		*dest = ft_join(*dest, ft_substr(which_one_first(*input), 0, tmp - which_one_first(*input)));
		if (tmp != *input + i + 1)
			space_end_case(&tmp, dest, what_case);
	}
	else
		*dest = ft_join(*dest, ft_substr(*input, 0, end));
	return (end);
}
