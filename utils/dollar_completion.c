/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/23 16:38:02 by rciaze           ###   ########.fr       */
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

	dup = ft_strdup(*dest);
	free(*dest);
	space_end_case(&dup, dest);
}

int	space_end_case(char **input, char **dest)
{
	int			i;
	char		*tmp;
	long int	end;

	i = 0;
	end = ft_strchr_rc(*input, ' ') - *input;
	if (end <= 0)
		end = ft_strlen(*input);
	while (input[0][i] && input[0][i] != '$' && i < end)
		i++;
	if (input[0][i] == '$' && (input[0][i + 1] != ' ' && input[0][i + 1]))
	{
		tmp = check_env_variables(input[0] + i);
		*dest = (ft_join(ft_substr(*input, 0, i), ft_strdup(tmp)));
	}
	else
		*dest = ft_substr(*input, 0, end);
	return (end);
}