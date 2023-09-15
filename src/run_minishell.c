/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:48:00 by wolf              #+#    #+#             */
/*   Updated: 2023/09/15 20:07:00 by wolf             ###   ########.fr       */
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

// POUR PIPEX --> PREMIERE CONDITION
void	loop_it(t_tmp_utils *tmp, t_cmd_and_opt *cmdopt, char *input, int i)
{
	if (input[i] && ft_strchr(input, '|'))
	{
		if (ft_strncmp(tmp->l_ety, input,
				ft_strlen(input) + ft_strlen(tmp->l_ety)))
			add_history(input);
	}
	else if (input[i])
	{
		create_command(input, cmdopt);
		if (ft_strncmp(tmp->l_ety, input,
				ft_strlen(input) + ft_strlen(tmp->l_ety)))
			add_history(input);
		if (!execute_command(cmdopt))
			return (free_tmp_utils(tmp), ft_exit(errno));
		update_last_sign(g_error_code);
	}
	else
		update_last_sign(0);
	if (get_last_sign() == 131)
		ft_printf("Quit (core dumped)\n");
}

// MINISHELL
void	minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt)
{
	t_tmp_utils	tmp;
	int			i;

	i = 0;
	tmp.l_ety = ft_strdup("");
	tmp.prompt = ft_strdup(prompt);
	free(prompt);
	while (input != NULL)
	{
		cmdopt->tmp_utils = tmp;
		if (ft_strncmp(input, "exit", 4) == 0
			&& (check_if_ifs(input[4]) || input[4] == '\0'))
			return (exit_func(cmdopt, input));
		while (check_if_ifs(input[i]))
			i++;
		loop_it(&tmp, cmdopt, input, i);
		free_cmdopt(cmdopt);
		tmp.l_ety = ft_strdup(input);
		tmp.prompt = display_user_prompt((char *)get_username());
		free_str(input);
		input = readline(tmp.prompt);
	}
	return (free_tmp_utils(&tmp));
}
