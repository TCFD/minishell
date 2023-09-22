/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:07:23 by wolf              #+#    #+#             */
/*   Updated: 2023/09/22 22:17:40 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	first_child(t_pipe *pipe_s)
{
	pipe_s->pid[0] = fork();
	if (pipe_s->pid[0] < 0)
		return (ft_printf("Minishell: fork error\n"), ft_exit(errno, true));
	if (pipe_s->pid[0] == 0)
	{
		dup2(pipe_s->pipe_fd[0][1], STDOUT_FILENO);
		close_all_pipes(pipe_s);
		execute_command(pipe_s->cmdopt_tab[0]);
		free_pipe(pipe_s);
		ft_exit(g_error_code, false);
	}
}

void	n_child(t_pipe *pipe_s, int *i)
{
	*i = 1;
	while (*i < pipe_s->nb_of_pipes)
	{
		pipe_s->pid[*i] = fork();
		if (pipe_s->pid[*i] < 0)
			return (perror(NULL));
		if (pipe_s->pid[*i] == 0)
		{
			dup2(pipe_s->pipe_fd[*i - 1][0], STDIN_FILENO);
			dup2(pipe_s->pipe_fd[*i][1], STDOUT_FILENO);
			close_all_pipes(pipe_s);
			execute_command(pipe_s->cmdopt_tab[*i]);
			free_pipe(pipe_s);
			ft_exit(g_error_code, false);
		}
		*i += 1;
	}
}

void	last_child(t_pipe *pipe_s, int *i)
{
	pipe_s->pid[*i] = fork();
	if (pipe_s->pid[*i] < 0)
		return (perror(NULL));
	if (pipe_s->pid[*i] == 0)
	{
		dup2(pipe_s->pipe_fd[*i - 1][0], STDIN_FILENO);
		close_all_pipes(pipe_s);
		execute_command(pipe_s->cmdopt_tab[*i]);
		free_pipe(pipe_s);
		ft_exit(g_error_code, false);
	}
}
