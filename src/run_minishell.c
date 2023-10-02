/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:48:00 by wolf              #+#    #+#             */
/*   Updated: 2023/10/02 16:24:35 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// EXIT FUNC

void	choose_launch_type(t_cmd_and_opt *cmdopt)
{
	if (!check_if_pipe(cmdopt->opt_ty_tb))
	{
		if (!execute_command(cmdopt))
			return (ft_exit(errno, true));
	}
	else
		launch_pipex(cmdopt);
}

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
		if (check_valid_file_name(cmdopt->opt_ty_tb.tab,
				cmdopt->opt_ty_tb.type))
			return (update_err_code(2));
		choose_launch_type(cmdopt);
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
		loop_it(cmdopt, input, i);
		free_cmdopt(cmdopt);
		update_last_entry(ft_strdup(input));
		update_prompt(display_user_prompt((char *)get_username()));
		free_str(&input);
		input = readline(get_prompt());
	}
	return (free_prompt_last_entry());
}
