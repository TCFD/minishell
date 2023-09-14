/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_correct_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:26:37 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/14 16:22:55 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
		{
			while (input[++i] && input[i] != '\'')
				;
			if (input[i] == '\0')
				return (1);
		}
		if (input[i] == '\"')
		{
			while (input[++i] && input[i] != '\"')
				;
			if (input[i] == '\0')
				return (1);
		}
	}
	return (0);
}

int	check_correct_quotes(char *input)
{
	if (check_input(input))
		return (0);
	return (1);
}
