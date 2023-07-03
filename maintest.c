/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/07/03 20:04:00 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// GETENV CHECK
char	*getenv_check(char *str)
{
	char	*found_it;

	found_it = ft_getenv(str);
	if (found_it == NULL)
		return (NULL);
	return (found_it);
}

// EXIT FUNC
void	exit_func(t_cmd_and_opt *cmdopt, char *input)
{
	free_cmdopt(cmdopt);
	free(input);
	rl_clear_history();
}

// MINISHELL
void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	while (input != NULL)
	{
		init_cmdopt(cmdopt);
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			return (exit_func(cmdopt, input));
		if (input[0])
		{
			create_command(input, cmdopt);
			add_history(input);
		}
		execute_command(cmdopt);
		if (input[0])
			free_cmdopt(cmdopt);
		free(input);
		prompt = display_user_prompt((char *)get_username());
		input = readline(prompt);
		free(prompt);
	}
	return ;
}

// RUN MINISHELL
void	run_minishell(char *user, t_cmd_and_opt *cmdopt)
{
	char	*input;
	char	*prompt;
	//char	**env;

	shlvl_plus_one();
	prompt = display_user_prompt((char *)get_username());
	input = readline(prompt);
	minishell(input, cmdopt, prompt);
	free(prompt);
	free(user);
	//env = get_env();
	//free_d_array(env);
	rl_clear_history();
	shlvl_minus_one();
}

// ----------- MAIN ----------- //
int	main(int ac, char **ag, char **env)
{
	t_cmd_and_opt	cmdopt;
	char			*user;

	//welcome_to_minishell();
	(void)ac;
	(void)ag;
	signal(SIGINT, sigint_handler);
	
	update_env(ft_d_strdup(env));
	verif_env_and_path(&cmdopt);
	create_command("/bin/whoami", &cmdopt);
	user = get_execve_return(&cmdopt);
	update_username(user);
	run_minishell(user, &cmdopt);
	
	return (0);
}
