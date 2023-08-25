/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/08/25 17:47:42 by tboldrin         ###   ########.fr       */
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
	char	*ipt;
	char	**spl;

	spl = ft_split(input, ' ');
	if (d_len(spl) > 2)
		return ((void)ft_printf("bash: exit: trop d'arguments\n"),
			free_cmdopt(cmdopt), free(input), free_d_array(spl),
			exit(1));
	if (spl[1])
		ipt = ft_strdup(spl[1]);
	else
		ipt = NULL;
	free_cmdopt(cmdopt);
	rl_clear_history();
	free(input);
	free_d_array(spl);
	exit_prg(ipt);
}

// MINISHELL
void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	int		i;
	char	*last_entry;

	i = 0;
	last_entry = ft_strdup("");
	while (input != NULL)
	{
		init_cmdopt(cmdopt);
		if (ft_strncmp(input, "exit", 4) == 0 && (check_if_IFS(input[4]) || input[4] == '\0'))
			return (free(last_entry), free(prompt), exit_func(cmdopt, input));
		while (check_if_IFS(input[i]))
			i++;
		if (input[i] && ft_strchr(input, '|'))
		{
			pipex(input);
			if (ft_strncmp(last_entry, input, ft_strlen(input) + ft_strlen(last_entry)))
				add_history(input);
		}
		else if (input[i])
		{
			create_command(input, cmdopt);
			if (ft_strncmp(last_entry, input, ft_strlen(input) + ft_strlen(last_entry)))
				add_history(input);
			if (!execute_command(cmdopt)) //-------// + 25 lignes
				return (free(prompt), free(last_entry), ft_exit(errno));
			update_last_sign(error_code);
		}
		else
			update_last_sign(0);
		if (get_last_sign() == 130)
			ft_printf("\n");
		if (get_last_sign() == 131)
			ft_printf("Quit (core dumped)\n");
		free_cmdopt(cmdopt);
		free(last_entry);
		last_entry = ft_strdup(input);
		free(input);
		free(prompt);
		prompt = NULL;
		prompt = display_user_prompt((char *)get_username());
		input = readline(prompt);
	}
	free(last_entry);
	free(prompt);
	return ;
}

// RUN MINISHELL
void	run_minishell(void)
{
	t_cmd_and_opt	cmdopt;
	char			*input;
	char			*prompt;
	char			*join;

	join = NULL;

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);

	
	shlvl_plus_one(&join);
	prompt = display_user_prompt((char *)get_username());
	input = readline(prompt);
	minishell(input, &cmdopt, prompt);
	//free(user);
	rl_clear_history();
	shlvl_minus_one();
	free_cmdopt(&cmdopt);
	//free(join);
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
	split_it = ft_split(find_path , ':');
	result = ft_strdup(split_it[d_len(split_it) - 2]);
	free(cmd);
	free_d_array(split_it);
	free(find_path);
	//free_cmdopt(&cmdopt);
	update_home_path(ft_strdup(result));
	free(result);
}

// ----------- MAIN ----------- //
int	main(int ac, char **ag, char **env)
{
	char	*user;
	//welcome_to_minishell();
	(void)ac;
	(void)ag;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	update_env(alloc_env(env));
	user = get_brut_cmd_result("/bin/whoami");
	update_username(ft_strdup(user));
	free(user);
	initialise_home_path();
	//if (ac > 2 && cmp(ag[1], "-c") && ag[2]) // POUR TESTER
	//	return (run_minishell_tester(ag + 2, &cmdopt), 0); // POUR TESTER
	run_minishell();
	printf("LAST error_code : %d\n", error_code);
	return (ft_exit(error_code), 0);
}
