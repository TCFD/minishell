/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:47:28 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 16:37:00 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int signum)
{
	if (!rl_done)
	{
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		ft_printf(2, "ctrl c pressed\n");
	}
	if (get_sign_ctrl() == 1)
		update_last_sign(-1);
	else
		update_last_sign(0);
	if (signum == SIGQUIT)
		return (update_err_code(131));
	else
		update_err_code(130);
}
