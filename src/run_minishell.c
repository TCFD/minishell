/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:48:00 by wolf              #+#    #+#             */
/*   Updated: 2023/09/27 14:37:48 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// EXIT FUNC
/* 
int	exit_func(char *input)
{
	char	*ipt;
	char	**spl;

	spl = ft_split(input, ' ');
	if (d_len(spl) > 2 && not_digit(spl[1]))
	{
		return ((void)ft_printf(2, "exit\nMinishell: exit: too many arguments."
			"\n"), free_d_array(spl), update_err_code(1), 1);
	}
	if (spl[1])
		ipt = ft_strdup(spl[1]);
	else
		ipt = NULL;
	rl_clear_history();
	free(input);
	free_d_array(spl);
	exit_prg(ipt);
	return (ft_exit(ft_atoi(ipt), true), 0);
} */

void	loop_it(t_cmd_and_opt *cmdopt, char *input, int i)
{
	int	minishell_call;

	minishell_call = 0;
	if (input[i])
	{
		if (input[i] == '#')
			return (check_to_add_history(input), (void)ft_printf(2, "\n"));
		create_command(input, cmdopt);
		minishell_call = check_if_input_minishell(cmdopt, input);
		if (minishell_call < 0)
			return ;
		check_to_add_history(input);
		if (!check_if_pipe(cmdopt->opt_ty_tb))
		{
			if (!execute_command(cmdopt))
				return (ft_exit(errno, true));
		}
		else
			launch_pipex(cmdopt);
		if (get_last_sign() < 0)
			check_sign_return(minishell_call);
	}
	else
		update_last_sign(0);
}

// MINISHELL
void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	int			i;

	i = 0;
	init_prompt_last_entry();
	update_last_entry(ft_strdup(" "));
	update_prompt(ft_strdup(prompt));
	free(prompt);
	while (input != NULL)
	{
		while (check_if_ifs(input[i]))
			i++;
		loop_it(cmdopt, input, i);
		// add_cmd_to_history_and_run(cmdopt, input, i);
		free_cmdopt(cmdopt);
		update_last_entry(ft_strdup(input));
		update_prompt(display_user_prompt((char *)get_username()));
		free_str(&input);
		input = readline(get_prompt());
		//input = readline("\x1b[36mminishell$\x1b[0m ");
	}
	return (free_prompt_last_entry());
}
