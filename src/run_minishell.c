/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:48:00 by wolf              #+#    #+#             */
/*   Updated: 2023/09/24 17:41:14 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
int	exit_func(t_cmd_and_opt *cmdopt, char *input)
{
	char	*ipt;
	char	**spl;

	spl = ft_split(input, ' ');
	if (d_len(spl) > 2)
		return ((void)ft_printf("Minishell: exit: too many arguments.\n"),
			free_d_array(spl), update_err_code(1), 1);
	if (spl[1])
		ipt = ft_strdup(spl[1]);
	else
		ipt = NULL;
	free_cmdopt(cmdopt);
	rl_clear_history();
	free(input);
	free_d_array(spl);
	exit_prg(ipt);
	return (ft_exit(0), 0);
}

void	check_to_add_history(char *input)
{
	if (ft_strncmp(get_last_entry(), input,
			ft_strlen(input) + ft_strlen(get_last_entry())))
		add_history(input);
}

void	loop_it(t_cmd_and_opt *cmdopt, char *input, int i)
{	
	int	minishell_call;

	minishell_call = 0;
	if (input[i])
	{
		if (input[i] == '#')
			return (check_to_add_history(input), (void)ft_printf("\n"));
		create_command(input, cmdopt);
		minishell_call = check_if_input_minishell(cmdopt, input);
		if (minishell_call < 0)
			return ;
		check_to_add_history(input);
		if (!execute_command(cmdopt))
			return (ft_exit(errno));
		if (get_last_sign() < 0)
			check_sign_return(minishell_call);
	}
	else
		update_last_sign(0);
	ft_printf("\n");
}

// MINISHELL
void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	int			check;
	int			i;

	i = 0;
	init_prompt_last_entry();
	update_last_entry(ft_strdup(" "));
	update_prompt(ft_strdup(prompt));
	free(prompt);
	while (input != NULL)
	{
		check = 0;
		if (ft_strncmp(input, "exit", 4) == 0
			&& (check_if_ifs(input[4]) || input[4] == '\0'))
			check = exit_func(cmdopt, input);
		while (check_if_ifs(input[i]))
			i++;
		add_cmd_to_history_and_run(check, cmdopt, input, i);
		free_cmdopt(cmdopt);
		update_last_entry(ft_strdup(input));
		update_prompt(display_user_prompt((char *)get_username()));
		free_str(&input);
		input = readline(get_prompt());
	}
	return (free_prompt_last_entry());
}
