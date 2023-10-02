/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:32:19 by wolf              #+#    #+#             */
/*   Updated: 2023/10/02 14:55:21 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_input_minishell(t_cmd_and_opt *cmdopt, char *input)
{
	if (cmp(cmdopt->command_name, "./minishell")
		&& minishell_with_arg(cmdopt))
		return (check_to_add_history(input), -1);
	if (cmp(cmdopt->command_name, "./minishell"))
		return (1);
	return (0);
}

void	check_sign_return(int minishell_call)
{
	if (minishell_call == 0)
	{
		if (g_error_code == 131)
			ft_printf(2, "Quit (core dumped)\n");
		else
			ft_printf(2, "\n");
	}
	update_last_sign(0);
}

int	is_digit(char *potential_digits)
{
	int	idx;

	idx = 0;
	if (potential_digits[idx] == '-'
		|| potential_digits[idx] == '+')
		idx++ ;
	while (potential_digits[idx] >= 48
		&& potential_digits[idx] <= 57)
		idx++ ;
	return (idx == ft_len(potential_digits));
}
