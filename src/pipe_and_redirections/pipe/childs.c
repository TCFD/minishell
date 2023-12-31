/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:07:23 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 14:29:11 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	first_child(t_pipe *pipe_s)
{
	int	exit_value;

	pipe_s->pid[0] = fork();
	if (pipe_s->pid[0] < 0)
		return (malloc_failure());
	if (pipe_s->pid[0] == 0)
	{
		dup2(pipe_s->pipe_fd[0][1], STDOUT_FILENO);
		close_all_pipes(pipe_s);
		execute_command(pipe_s->cmdopt_tab[0]);
		if (cmp(pipe_s->cmdopt_tab[0]->command_name, "exit"))
			exit_value = g_error_code;
		else
			exit_value = errno;
		ft_exit(exit_value, false);
	}
}

void	n_child(t_pipe *pipe_s, int *i)
{
	int	exit_value;

	*i = 1;
	while (*i < pipe_s->nb_of_pipes)
	{
		pipe_s->pid[*i] = fork();
		if (pipe_s->pid[*i] < 0)
			return (malloc_failure());
		if (pipe_s->pid[*i] == 0)
		{
			dup2(pipe_s->pipe_fd[*i - 1][0], STDIN_FILENO);
			dup2(pipe_s->pipe_fd[*i][1], STDOUT_FILENO);
			close_all_pipes(pipe_s);
			execute_command(pipe_s->cmdopt_tab[*i]);
			if (cmp(pipe_s->cmdopt_tab[*i]->command_name, "exit"))
				exit_value = g_error_code;
			else
				exit_value = errno;
			ft_exit(exit_value, false);
		}
		*i += 1;
	}
}

void	check_first_exit_arg(t_cmd_and_opt *cmdopt)
{
	char	**tab;

	tab = cmdopt->opt_ty_tb.tab;
	if (d_len(tab) == 2 && is_digit(tab[1]))
		return (ft_exit_pipex(ft_atoi(tab[1]) % 256, false));
	if (d_len(tab) > 2 && is_digit(tab[1]))
		return (ft_exit_pipex(1, false));
	else if (d_len(tab) == 1)
		return (ft_exit_pipex(0, false));
}

void	last_child(t_pipe *pipe_s, int *i)
{
	pipe_s->pid[*i] = fork();
	if (pipe_s->pid[*i] < 0)
		return (malloc_failure());
	if (pipe_s->pid[*i] == 0)
	{
		dup2(pipe_s->pipe_fd[*i - 1][0], STDIN_FILENO);
		close_all_pipes(pipe_s);
		execute_command(pipe_s->cmdopt_tab[*i]);
		if (cmp(pipe_s->cmdopt_tab[*i]->command_name, "exit"))
			check_first_exit_arg(pipe_s->cmdopt_tab[*i]);
		ft_exit(g_error_code, false);
	}
}
