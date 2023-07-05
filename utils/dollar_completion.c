/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:39 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/05 20:38:01 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Regarde dans l'environement si la variable existe, si oui, la remplace par sa valeur

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
		return (free(value), ft_itoa(error_code));
	return_value = ft_strdup(ft_getenv(value + 1));
	free (value);
	return (return_value);
}
