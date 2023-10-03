/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/10/03 19:59:59 by tboldrin         ###   ########.fr       */
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
	free_cmdopt(&cmdopt);
}

char	*ft_strdup_protect(char *str)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (!new_str)
		return (malloc_failure(), NULL);
	//garbage_add((void **)&new_str);
	return (new_str);
}

char	**alloc_env(char **env)
{
	char	**env_out;
	int		idx;

	idx = 0;
	
	env_out = malloc((d_len(env) + 1) * sizeof(char *));
	if (!env_out)
		return (ft_exit(EXIT_FAILURE, true), NULL);
	//garbage_add_triple((void ***)&env_out);
	/* char *str1 = ft_strdup("test1");
	garbage_add((void **)&str1);
	char *str2 = ft_strdup("test2");
	garbage_add((void **)&str2); */
	while (env[idx])
	{
		env_out[idx] = ft_strdup_protect(env[idx]);
		//garbage_add((void **)&env_out[idx]);
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
	free(user);
	initialise_home_path();
	run_minishell();
	if (get_fix_env_detection() == 1)
		ft_printf(STDERR_FILENO, "\n");
	return (ft_exit(g_error_code, true), 0);
}
