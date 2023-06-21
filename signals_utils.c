/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:47:28 by wolf              #+#    #+#             */
/*   Updated: 2023/06/21 12:20:39 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(void)
{
	char	*prompt;

	rl_redisplay();
	ft_printf("\n");
	rl_replace_line("", 0);
	prompt = display_user_prompt();
	ft_printf("%s", prompt);
	free(prompt);
}
