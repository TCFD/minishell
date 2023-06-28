/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/06/28 15:28:00 by rciaze           ###   ########.fr       */
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

void	exit_func(t_cmd_and_opt *cmdopt, char *input)
{
	free_cmdopt(cmdopt);
	free(input);
	rl_clear_history();
}

void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	while (input != NULL)
	{
		init_cmdopt(cmdopt);
		if (ft_strncmp(input, "exit", 4) == 0)
			return (exit_func(cmdopt, input));
		if (input[0])
		{
			create_command(input, cmdopt);
			add_history(input);
		}
		execute_command(cmdopt);
		free(input);
		free_cmdopt(cmdopt);
		prompt = display_user_prompt((char *)get_username());
		input = readline(prompt);
		free(prompt);
	}
	return ;
}

void	update_value(const char *new_value)
{
	static char	*last_value;

	last_value = NULL;
	if (last_value != NULL)
		free(last_value);
	last_value = strdup(new_value);
}

int	main(int ac, char **ag, char **env)
{
	t_cmd_and_opt	cmdopt;
	char			*prompt;
	char			*input;
	char			*user;

	//welcome_to_minishell();
	(void)ac;
	(void)ag;
	(void)env;
	//for (int i=0; env[i]; i++)
	//	ft_printf("%s\n", env[i]);
	signal(SIGINT, sigint_handler);
	//remettre le PATH si unset dans le shell parent
	create_command("/bin/whoami", &cmdopt);
	user = get_execve_return(&cmdopt);
	ft_printf("user : %s\n", user);
	free_cmdopt(&cmdopt);
	update_username(user);
	prompt = display_user_prompt((char *)get_username());
	input = readline(prompt);
	minishell(input, &cmdopt, prompt);
	free(prompt);
	free(user);
	rl_clear_history();
	return (0);
}
