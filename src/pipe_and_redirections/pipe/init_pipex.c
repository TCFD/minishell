/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:20:45 by zbp15             #+#    #+#             */
/*   Updated: 2023/10/04 16:57:14 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	init_sub_cmdopt(t_pipe *pipe_s, t_cmd_and_opt *cmdopt)
{
	int				i;
	int				j;
	int				next_pipe;

	i = -1;
	j = 0;
	while (++i < pipe_s->nb_of_forks)
	{
		next_pipe = get_next_pipe(cmdopt->opt_ty_tb, j);
		pipe_s->cmdopt_tab[i] = ft_calloc(sizeof(t_cmd_and_opt), 1);
		if (!pipe_s->cmdopt_tab[i])
			return (ft_printf(STDERR_FILENO, "Minishell: ft_malloc error\n"),
				ft_exit(errno, true));
		get_new_cmdopt(pipe_s->cmdopt_tab[i], cmdopt, j, next_pipe);
		j = next_pipe + 1;
	}
}

void	init_pipes(t_pipe *pipe_s)
{
	int	i;

	i = -1;
	while (++i < pipe_s->nb_of_pipes)
	{
		pipe_s->pipe_fd[i] = ft_calloc(sizeof(int), 2);
		if (pipe_s->pipe_fd[i] == NULL)
			return (ft_printf(STDERR_FILENO, "Minishell: ft_calloc error\n"),
				ft_exit(errno, true));
		if (pipe(pipe_s->pipe_fd[i]) < 0)
			return (ft_printf(STDERR_FILENO, "Minishell: pipe error\n"),
				ft_exit(errno, true));
	}
}

void	init_pipex(t_pipe *pipe_s, t_cmd_and_opt *cmdopt)
{
	pipe_s->nb_of_pipes = count_pipes(cmdopt->opt_ty_tb);
	pipe_s->nb_of_forks = pipe_s->nb_of_pipes + 1;
	malloc_pipes(pipe_s);
	init_sub_cmdopt(pipe_s, cmdopt);
	init_pipes(pipe_s);
}
