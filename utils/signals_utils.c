/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:47:28 by wolf              #+#    #+#             */
/*   Updated: 2023/08/18 17:25:47 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signum)
{
	char	*prompt;

	if (get_sign_ctrl() == 0)
		rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (get_sign_ctrl() == 0)
	{
		prompt = display_user_prompt((char *)get_username());
		ft_printf("\n%s", prompt);
		free(prompt);
	}
	else
	{
		if (signum == 3)
			ft_printf("Quit (core dumped)");
		ft_printf("\n");
	}
	if (signum == 3)
		update_err_code(131);
	else
		update_err_code(130);
}