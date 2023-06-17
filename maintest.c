/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 20:16:34 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ----
char	*getenv_check(char *str)
{
	char	*found_it;

	found_it = getenv(str);
	if (found_it == NULL)
		return (NULL);
	return (found_it);
}


int	main(void)
{
	t_cmd_and_opt	cmdopt;
	char			*prompt;
	char			*input;

	//welcome_to_minishell();
	signal(SIGINT, sigint_handler);
	prompt = display_user_prompt();
	while ((input = readline(prompt)) != NULL && ft_strncmp(input, "exit", 4) != 0)
	{
		init_cmdopt(&cmdopt);
		if (input[0])
		{
			create_command(input, &cmdopt);
			add_history(input);
		}
		execute_command(&cmdopt);
		free(input);
		free_cmdopt(&cmdopt);
	}
	free(prompt);
	return (0);
}
