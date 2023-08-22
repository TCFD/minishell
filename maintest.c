/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/08/22 15:14:21 by tboldrin         ###   ########.fr       */
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
void    exit_func(t_cmd_and_opt *cmdopt, char *input)
{
    char    *ipt;
    char    **spl;
	char	*env_var;

    spl = ft_split(input, ' ');
    if (d_len(spl) > 2)
        return ((void)printf("bash: exit: trop d'arguments\n"),
            free_cmdopt(cmdopt), free(input), free_d_array(spl),
            exit(1));
    if (spl[1])
        ipt = ft_strdup(spl[1]);
    else
	{
        ipt = NULL;
	}	
	env_var = get_env_var("PWD=");
	free(env_var);
	env_var = get_env_var("OLDPWD=");
	free(env_var);
    free_cmdopt(cmdopt);
    rl_clear_history();
    free(input);
    free_d_array(spl);
    ft_exit(ipt);
}

// MINISHELL
void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	int		i;
	char	*last_entry;

	i = 0;
	last_entry = ft_strdup(NULL);
	while (input != NULL)
	{
		init_cmdopt(cmdopt);
		if (ft_strncmp(input, "exit", 4) == 0 && (check_if_IFS(input[4]) || input[4] == '\0'))
			return (free(last_entry), exit_func(cmdopt, input));
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
			execute_command(cmdopt);
		}
		else
			update_err_code(0);
		free_cmdopt(cmdopt);
		free(last_entry);
		last_entry = ft_strdup(input);
		free(input);
		prompt = display_user_prompt((char *)get_username());
		input = readline(prompt);
		free(prompt);
		prompt = NULL;
	}
	free(last_entry);
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

// ----------- MAIN ----------- //
int	main(int ac, char **ag, char **env)
{
	t_cmd_and_opt	cmdopt;
	char			*user;

	//welcome_to_minishell();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	update_env(alloc_env(env));
	verif_env_and_path(&cmdopt);
	create_command("/bin/whoami", &cmdopt);
	free(cmdopt.opt_ty_tb.tab[0]);
	cmdopt.opt_ty_tb.tab[0] = ft_strdup(cmdopt.command_path);
	user = get_execve_return(&cmdopt);
	update_username(user);
	free_cmdopt(&cmdopt);
	if (ac > 2 && cmp(ag[1], "-c") && ag[2]) // POUR TESTER
		return (run_minishell_tester(ag + 2, &cmdopt), 0); // POUR TESTER
	run_minishell(user, &cmdopt);
	free_env_singleton();
	//exit_message(0);
	return (0);
}
