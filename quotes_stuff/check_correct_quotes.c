/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_correct_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:26:37 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/19 19:32:24 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_input(char *input, int *simple_q, int *double_q)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
			*simple_q += 1;
		if (input[i] == '\"')
			*double_q += 1;
	}
}

int	check_correct_quotes(char *input)
{
	int	simple_quote_counter;
	int	double_quotes_counter;

	simple_quote_counter = 0;
	double_quotes_counter = 0;
	check_input(input, &simple_quote_counter, &double_quotes_counter);
	if (simple_quote_counter % 2 || double_quotes_counter % 2)
		return (0);
	return (1);
}
