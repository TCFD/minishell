/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/09/25 16:29:55 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// RUN MINISHELL
void	run_minishell(void)
{
	t_cmd_and_opt	cmdopt;
	char			*input;
	char			*prompt;\e

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);
	env_var_plus_one("SHLVL");
	//one_time_animation_start();
	prompt = display_user_prompt((char *)get_username());
	input = readline(prompt);
	minishell(input, &cmdopt, prompt);
	rl_clear_history();
	env_var_minus_one("SHLVL");
	free_cmdopt(&cmdopt);
}

char	**alloc_env(char **env)
{
	char	**env_out;
	int		idx;

	idx = 0;
	env_out = malloc((d_len(env) + 1) * sizeof(char *));
	if (!env_out)
		return (exit(EXIT_FAILURE), NULL);
	while (env[idx])
	{
		env_out[idx] = ft_strdup(env[idx]);
		if (!env_out[idx])
			return (free(env_out), exit(EXIT_FAILURE), NULL);
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
		return (
			ft_printf("\n\t\001\e[32m\002./minishell\001\e[m\002 does not"
				" take any arguments.\n"),
			ft_printf("\n\tRead minishell man. End of program.\n"), 1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	update_env(alloc_env(env));
	user = get_brut_cmd_result("/bin/whoami");
	update_username(ft_strdup(user));
	free(user);
	initialise_home_path();
	run_minishell();
	if (get_fix_env_detection() == 1)
		ft_printf(STDERR_FILENO, "\n");
	return (ft_exit(g_error_code, true), 0);
}
