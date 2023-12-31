/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:48:20 by wolf              #+#    #+#             */
/*   Updated: 2023/09/25 16:43:37 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minishell_with_arg(t_cmd_and_opt *cmdopt)
{
	int	fail;

	fail = 0;
	if (cmdopt->opt_ty_tb.tab[1])
	{
		ft_printf(2, "Minishell: minishell does not take any arguments.\n\n");
		update_err_code(1);
		fail = 1;
	}
	change_underscore_value(cmdopt, false);
	return (fail);
}
