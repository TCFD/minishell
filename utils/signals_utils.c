/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:47:28 by wolf              #+#    #+#             */
/*   Updated: 2023/08/15 22:26:36 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signum)
{
	char	*prompt;

	(void)(signum);
	rl_replace_line("", 0);
	rl_redisplay();
	if (get_sign_ctrl() == 0)
	{
		prompt = display_user_prompt((char *)get_username());
		ft_printf("\n%s", prompt);
		free(prompt);
	}
	else
		printf("\n");
	update_err_code(130);
}