/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:18:58 by zbp15             #+#    #+#             */
/*   Updated: 2023/10/04 18:56:33 by tboldrin         ###   ########.fr       */
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

void	malloc_pipes(t_pipe *pipe_s)
{
	pipe_s->cmdopt_tab = ft_calloc(sizeof(t_cmd_and_opt *),
			pipe_s->nb_of_forks);
	pipe_s->pid = ft_calloc(sizeof(int), pipe_s->nb_of_forks);
	pipe_s->pipe_fd = ft_calloc(sizeof(int [2]), pipe_s->nb_of_pipes);
}

void	ft_exit_pipex(int code, bool msg)
{
	if (msg)
		ft_printf(STDOUT_FILENO, "exit\n");
	update_pwd(NULL);
	free_garbage();
	exit(code);
}
