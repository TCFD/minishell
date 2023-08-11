/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/08/11 23:29:09 by wolf             ###   ########.fr       */
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
	
    spl = ft_split(input, ' ');
    if (d_len(spl) > 2)
        return ((void)printf("bash: exit: trop d'arguments\n"),
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
		if (input[i] && ft_strchr(input, '|'))
		{
			pipex(input);
			add_history(input);
		}
		else if (input[i])
		{
			create_command(input, cmdopt);
			add_history(input);
			execute_command(cmdopt);
		}
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
	free(cmdopt.opt_ty_tb.tab[0]);
	cmdopt.opt_ty_tb.tab[0] = ft_strdup(cmdopt.command_path);
	user = get_execve_return(&cmdopt);
	update_username(user);
	free_cmdopt(&cmdopt);
	if (ac > 2 && cmp(ag[1], "-c") && ag[2]) // POUR TESTER
		return (run_minishell_tester(ag + 2, &cmdopt), 0); // POUR TESTER
	run_minishell(user, &cmdopt);
	return (0);
}
