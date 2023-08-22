/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:47:28 by wolf              #+#    #+#             */
/*   Updated: 2023/08/22 16:12:30 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int signum)
{
	char	*prompt;

	rl_replace_line("", 0);
	if (get_sign_ctrl() == 0)
		ft_printf("\n");
	rl_redisplay();
	if (signum == 3)
		update_err_code(131);
	else
		update_err_code(130);
	if (get_sign_ctrl() == 0)
	{
		prompt = display_user_prompt((char *)get_username());
		ft_printf("%s", prompt);
		free(prompt);
	}
	else
	{
		if (signum == 3)
			ft_printf("Quit (core dumped)");
		ft_printf("\n");
	}
}