/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/10/09 15:00:06 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// RUN MINISHELL
void	run_minishell(void)
{
	t_cmd_and_opt	cmdopt;
	char			*input;
	char			*prompt;

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);
	env_var_plus_one("SHLVL");
	//one_time_animation_start();
	prompt = display_user_prompt((char *)get_username());
	input = readline(prompt);
	minishell(input, &cmdopt, prompt);
	rl_clear_history();
	env_var_minus_one("SHLVL");
}

char	**alloc_env(char **env)
{
	char	**env_out;
	int		idx;

	idx = 0;
	env_out = ft_malloc((d_len(env) + 1) * sizeof(char *));
	while (env[idx])
	{
		env_out[idx] = ft_strdup(env[idx]);
		idx++ ;
	}
	env_out[idx] = NULL;
	return (env_out);
}

int	main(int ac, char **ag, char **env)
{
	char	*user;

	(void)ag;
	if (ac > 1)
	{
		ft_printf(2, "\n\t\001\e[32m\002./minishell\001\e[m\002");
		ft_printf(2, " does not take any arguments.\n");
		ft_printf(2, "\n\tRead minishell man. End of program.\n");
		return (1);
	}
	start_garbage();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	update_env(alloc_env(env));
	user = get_brut_cmd_result("/bin/whoami");
	update_username(ft_strdup(user));
	initialise_home_path();
	run_minishell();
	if (get_fix_env_detection() == 1)
		ft_printf(STDERR_FILENO, "\n");
	return (ft_exit(g_error_code, true), 0);
}
