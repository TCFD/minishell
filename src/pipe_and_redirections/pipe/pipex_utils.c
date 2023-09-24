/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:18:58 by zbp15             #+#    #+#             */
/*   Updated: 2023/09/24 21:23:23 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	close_all_pipes(t_pipe *pipe_s)
{
	int	i;

	i = -1;
	while (++i < pipe_s->nb_of_pipes)
	{
		close(pipe_s->pipe_fd[i][0]);
		close(pipe_s->pipe_fd[i][1]);
	}
}

void	free_pipe(t_pipe *pipe_s)
{
	int	i;

	i = -1;
	while (++i < pipe_s->nb_of_forks)
	{
		if (i < pipe_s->nb_of_pipes)
			free(pipe_s->pipe_fd[i]);
		free_cmdopt(pipe_s->cmdopt_tab[i]);
		free(pipe_s->cmdopt_tab[i]);
	}
	free(pipe_s->cmdopt_tab);
	free(pipe_s->pid);
	free(pipe_s->pipe_fd);
}

void	malloc_pipes(t_pipe *pipe_s)
{
	pipe_s->cmdopt_tab = ft_calloc(sizeof(t_cmd_and_opt *),
			pipe_s->nb_of_forks);
	pipe_s->pid = ft_calloc(sizeof(int), pipe_s->nb_of_forks);
	pipe_s->pipe_fd = ft_calloc(sizeof(int [2]), pipe_s->nb_of_pipes);
	if (!pipe_s->pid || !pipe_s->pipe_fd || !pipe_s->cmdopt_tab)
	{
		return (ft_printf(STDERR_FILENO, "Minishell: malloc error\n"),
			ft_exit(errno, true));
	}
}
