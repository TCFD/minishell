/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/06/30 15:29:31 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ----
char	*getenv_check(char *str)
{
	char	*found_it;

	found_it = ft_getenv(str);
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

void	run_minishell(char *user, t_cmd_and_opt *cmdopt)
{
	char	*input;
	char	*prompt;

	shlvl_plus_one();
	prompt = display_user_prompt((char *)get_username());
	input = readline(prompt);
	minishell(input, cmdopt, prompt);
	free(prompt);
	free(user);
	rl_clear_history();
	shlvl_minus_one();
}

int	main(int ac, char **ag, char **env)
{
	t_cmd_and_opt	cmdopt;
	char			*user;

	//welcome_to_minishell();
	(void)ac;
	(void)ag;
	signal(SIGINT, sigint_handler);
	
	update_env(env);
	verif_env_and_path(&cmdopt);
	ft_printf("cmdopt.env_i : %d\n", cmdopt.path_unset);
	
	create_command("/bin/whoami", &cmdopt);
	user = get_execve_return(&cmdopt);
	update_username(user);
	run_minishell(user, &cmdopt);
	
	return (0);
}
