/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/07/06 12:18:53 by rciaze           ###   ########.fr       */
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
	char	ipt[1024];
	char	**spl;

	spl = ft_split(input, ' ');

	if (spl[1])
		ft_strlcpy(ipt, spl[1], ft_strlen(spl[1]) + 1);	
	free_cmdopt(cmdopt);
	rl_clear_history();
	free(input);
	free_d_array(spl);
	ft_exit(ipt);
}

// MINISHELL
void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	int	i;
	
	i = 0;
	while (input != NULL)
	{
		init_cmdopt(cmdopt);
		if (ft_strncmp(input, "exit", 4) == 0)
			return (exit_func(cmdopt, input));
		while (input[i] == ' ')
			i++;
		if (input[i])
		{
			create_command(input, cmdopt);
			add_history(input);
		}
		execute_command(cmdopt);
		if (input[i])
			free_cmdopt(cmdopt);
		free(input);
		prompt = display_user_prompt((char *)get_username());
		input = readline(prompt);
		free(prompt);
		prompt = NULL;
	}
	return ;
}

// RUN MINISHELL
void	run_minishell(char *user, t_cmd_and_opt *cmdopt)
{
	char	*input;
	char	*prompt;
	char	*join;

	join = NULL;
	shlvl_plus_one(&join);
	prompt = display_user_prompt((char *)get_username());
	input = readline(prompt);
	minishell(input, cmdopt, prompt);
	free(prompt);
	free(user);
	rl_clear_history();
	shlvl_minus_one();
	free_cmdopt(cmdopt);
	free(join);
}

// ----------- MAIN ----------- //
int	main(int ac, char **ag, char **env)
{
	t_cmd_and_opt	cmdopt;
	char			*user;

	//welcome_to_minishell();
	
	signal(SIGINT, sigint_handler);
	update_env(env);
	verif_env_and_path(&cmdopt);
	create_command("/bin/whoami", &cmdopt);
	user = get_execve_return(&cmdopt);
	update_username(user);
	if (ac > 2 && cmp(ag[1], "-c") && ag[2]) // POUR TESTER
		return (run_minishell_tester(ag + 2, &cmdopt), 0); // POUR TESTER
	free_cmdopt(&cmdopt);
	run_minishell(user, &cmdopt);
	return (0);
}
