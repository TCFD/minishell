/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/08/18 18:39:32 by rciaze           ###   ########.fr       */
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
	char	*env_free;
    //char    **spl;
	
    //spl = ft_split(input, ' ');
	
	create_command(input, cmdopt);
    if (d_len(cmdopt->opt_ty_tb.tab) > 2)
        return ((void)printf("Minishell: exit: trop d'arguments\n"),
            free_cmdopt(cmdopt), free(input),
            exit(1));
    if (cmdopt->opt_ty_tb.tab[1])
        ipt = ft_strdup(cmdopt->opt_ty_tb.tab[1]);
    else
	{
        ipt = NULL;
	}	
	env_free = get_env_var("PWD=");
	free(env_free);
	env_free = get_env_var("OLDPWD=");
	free(env_free);
    free_cmdopt(cmdopt);
    rl_clear_history();
    free(input);
    ///free_d_array(spl);
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
	free(join);
}

// ----------- MAIN ----------- //
int	main(int ac, char **ag, char **env)
{
	t_cmd_and_opt	cmdopt;
	char			*user;

	//welcome_to_minishell();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
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
