/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:47:28 by wolf              #+#    #+#             */
/*   Updated: 2023/09/10 16:51:05 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int signum)
{
	if (!rl_done)
	{
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	if (signum == SIGQUIT)
		update_err_code(131);
	else
		update_err_code(130);
}
