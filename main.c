/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/09/12 17:32:51 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// RUN MINISHELL
void	run_minishell(void)
{
	t_cmd_and_opt	cmdopt;
	char			*input;
	char			*prompt;

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);
	env_var_plus_one("SHLVL");
	one_time_animation_start();
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

char	*get_brut_cmd_result(char *cmd)
{
	t_cmd_and_opt	cmdopt;
	char			*result;

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);
	create_command(cmd, &cmdopt);
	free(cmdopt.opt_ty_tb.tab[0]);
	cmdopt.opt_ty_tb.tab[0] = ft_strdup(cmdopt.command_path);
	result = get_execve_return(&cmdopt);
	free_cmdopt(&cmdopt);
	return (result);
}

void	initialise_home_path(void)
{
	t_cmd_and_opt	cmdopt;
	char			*find_path;
	char			**split_it;
	char			*result;
	char			*cmd;

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);
	cmd = ft_join(ft_strdup("/bin/getent passwd "), ft_strdup(get_username()));
	find_path = get_brut_cmd_result(cmd);
	split_it = ft_split(find_path, ':');
	result = ft_strdup(split_it[d_len(split_it) - 2]);
	free(cmd);
	free_d_array(split_it);
	free(find_path);
	update_home_path(ft_strdup(result));
	free(result);
}

int	main(int ac, char **ag, char **env)
{
	char	*user;

	(void)ac;
	(void)ag;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	update_env(alloc_env(env));
	user = get_brut_cmd_result("/bin/whoami");
	update_username(ft_strdup(user));
	free(user);
	initialise_home_path();
	run_minishell();
	if (get_fix_env_detection() == 1)
		printf("\n");
	one_time_animation_end();
	return (ft_exit(g_error_code), 0);
}
