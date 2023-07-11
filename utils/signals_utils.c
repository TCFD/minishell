/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:47:28 by wolf              #+#    #+#             */
/*   Updated: 2023/06/28 11:05:27 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signum)
{
	char	*prompt;

	(void)(signum);
	rl_replace_line("", 0);
	rl_redisplay();
	prompt = display_user_prompt((char *)get_username());
	ft_printf("\n%s", prompt);
	free(prompt);
}
