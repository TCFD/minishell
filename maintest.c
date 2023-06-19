/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/06/19 18:25:14 by tboldrin         ###   ########.fr       */
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

void	exit_func(t_cmd_and_opt *cmdopt, char *prompt, char *input)
{
	free_cmdopt(cmdopt);
	free(input);
	free(prompt);
	rl_clear_history();
}


void	abcdef(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	while (input != NULL)
	{
		init_cmdopt(cmdopt);
		if (ft_strncmp(input, "exit", 4) == 0)
			return  (exit_func(cmdopt, prompt, input));
		if (input[0])
		{
			create_command(input, cmdopt);
			add_history(input);
		}
		execute_command(cmdopt);
		free(input);
		free_cmdopt(cmdopt);
		input = readline(prompt);
	}
	return ;
}

int	main(void)
{
	t_cmd_and_opt	cmdopt;
	char			*prompt;
	char			*input;

	//welcome_to_minishell();
	signal(SIGINT, sigint_handler);
	prompt = display_user_prompt();
	input = readline(prompt);

	abcdef(input, &cmdopt, prompt);
	
	free(prompt);
	rl_clear_history();
	return (0);
}
