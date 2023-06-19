/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_correct_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:26:37 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/19 17:00:29 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_option(t_cmd_and_opt *cmdopt, int *simple_q, int *double_q)
{
	int	i;
	int	j;

	i = -1;
	while (cmdopt->option[++i])
	{
		printf("opt \"%s\"\n", cmdopt->option[i]);
		j = -1;
		while (cmdopt->option[i][++j])
		{
			if (cmdopt->option[i][j] == '\'')
				*simple_q += 1;
			if (cmdopt->option[i][j] == '\"')
				*double_q += 1;
		}
	}
}

void	check_name(t_cmd_and_opt *cmdopt, int *simple_q, int *double_q)
{
	int	i;

	i = -1;
	while (cmdopt->command_name[++i])
	{
		if (cmdopt->command_name[i] == '\'')
			*simple_q += 1;
		if (cmdopt->command_name[i] == '\"')
			*double_q += 1;
	}
}

int	check_correct_quotes(t_cmd_and_opt *cmdopt)
{
	int	simple_quote_counter;
	int	double_quotes_counter;

	simple_quote_counter = 0;
	double_quotes_counter = 0;
	if (cmdopt->option)
		check_option(cmdopt, &simple_quote_counter, &double_quotes_counter);
	else if (cmdopt->command_name)
		check_name(cmdopt, &simple_quote_counter, &double_quotes_counter);
	if (simple_quote_counter % 2 || double_quotes_counter % 2)
		return (0);
	return (1);
}
