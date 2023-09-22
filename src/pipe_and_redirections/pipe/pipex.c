/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:14:17 by wolf              #+#    #+#             */
/*   Updated: 2023/09/22 19:33:24 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_pipes(t_opt_tab opt)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (opt.tab[i])
	{
		if (opt.tab[i][0] == '|' && opt.type[i] != SIMPLE_Q
			&& opt.type[i] != DOUBLE_Q)
			counter++;
		i++;
	}
	return (counter);
}

int	get_next_pipe(t_opt_tab opt, int j)
{
	while (opt.tab[j])
	{
			if (opt.tab[j][0] == '|' && opt.type[j] != SIMPLE_Q
			&& opt.type[j] != DOUBLE_Q)
			return (j);
		j++;
	}
	return (d_len(opt.tab));
}

void	get_new_cmdopt(t_cmd_and_opt *new, t_cmd_and_opt *old, int st, int end)
{
	int	i;
	int	j;
	
	new->opt_ty_tb.tab = ft_calloc(end - st + 1, sizeof(char *));
	new->opt_ty_tb.type = ft_calloc(end - st + 1, sizeof(char));
	i = st;
	j = 0;
	while (i < end)
	{
		new->opt_ty_tb.tab[j] = ft_strdup(old->opt_ty_tb.tab[i]);
		new->opt_ty_tb.type[j] = old->opt_ty_tb.type[i];
		i++;
		j++;
	}
	new->opt_ty_tb.tab[j] = NULL;
	new->opt_ty_tb.type[j] = '\0';
	new->command_name = ft_strdup(new->opt_ty_tb.tab[0]);
	new->command_path = create_path(ft_strdup(new->opt_ty_tb.tab[0]), 1);
	new->is_child = true;
}

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

void	launch_pipex(t_cmd_and_opt *cmdopt)
{
	t_cmd_and_opt	**cmdopt_tab;
	t_pipe			pipe_s;
	int				i;
	int				j;
	int				next_pipe;

	pipe_s.nb_of_pipes = count_pipes(cmdopt->opt_ty_tb);
	pipe_s.nb_of_forks = pipe_s.nb_of_pipes + 1;
	cmdopt_tab = ft_calloc(sizeof(t_cmd_and_opt *), pipe_s.nb_of_forks);
	pipe_s.pid = ft_calloc(sizeof(int), pipe_s.nb_of_forks);
	pipe_s.pipe_fd = ft_calloc(sizeof(int [2]), pipe_s.nb_of_pipes);
	if (!pipe_s.pid || !pipe_s.pipe_fd || !cmdopt_tab)
		return (ft_printf("Minishell: malloc error\n"), ft_exit(errno, true));
	i = -1;
	j = 0;
	while (++i < pipe_s.nb_of_forks)
	{
		next_pipe = get_next_pipe(cmdopt->opt_ty_tb, j);
		cmdopt_tab[i] = ft_calloc(sizeof(t_cmd_and_opt), 1);
		if (!cmdopt_tab[i])
			return (ft_printf("Minishell: malloc error\n"), ft_exit(errno, true));
		get_new_cmdopt(cmdopt_tab[i], cmdopt, j, next_pipe);
		j = next_pipe + 1;
	}
	/* for (int k = -1; ++k < pipe_s.nb_of_forks;)
	{
		printf("cmdopt_tab[%d]->command_name = %s\n", k, cmdopt_tab[k]->command_name);
		for (int q = -1; ++q < d_len(cmdopt_tab[k]->opt_ty_tb.tab);)
		{
			printf("\tcmdopt_tab[%d]->opt_ty_tb.tab[%d] = %s\n", k, q, cmdopt_tab[k]->opt_ty_tb.tab[q]);
		}
	} */
	i = -1;
	while (++i < pipe_s.nb_of_pipes)
	{
		pipe_s.pipe_fd[i] = ft_calloc(sizeof(int), 2);
		if (pipe_s.pipe_fd[i] == NULL)
			return (ft_printf("Minishell: ft_calloc error\n"), ft_exit(errno, true));
		if (pipe(pipe_s.pipe_fd[i]) < 0)
			return (ft_printf("Minishell: pipe error\n"), ft_exit(errno, true));
	}
	pipe_s.pid[0] = fork();
	if (pipe_s.pid[0] < 0)
		return (ft_printf("Minishell: fork error\n"), ft_exit(errno, true));
	if (pipe_s.pid[0] == 0)
	{
		dup2(pipe_s.pipe_fd[0][1], STDOUT_FILENO);
		close_all_pipes(&pipe_s);
		execute_command(cmdopt_tab[0]);
	}
	i = 1;
	while (i < pipe_s.nb_of_pipes)
	{
		pipe_s.pid[i] = fork();
		if (pipe_s.pid[i] < 0)
			return (perror(NULL));
		if (pipe_s.pid[i] == 0)
		{
			dup2(pipe_s.pipe_fd[i - 1][0], STDIN_FILENO);
			dup2(pipe_s.pipe_fd[i][1], STDOUT_FILENO);
			close_all_pipes(&pipe_s);
			execute_command(cmdopt_tab[i]);
		}
		i++;
	}
	pipe_s.pid[i] = fork();
	if (pipe_s.pid[i] < 0)
		return (perror(NULL));
	if (pipe_s.pid[i] == 0)
	{
		dup2(pipe_s.pipe_fd[i - 1][0], STDIN_FILENO);
		close_all_pipes(&pipe_s);
		execute_command(cmdopt_tab[i]);
	}
	close_all_pipes(&pipe_s);
	i = -1;
	while (++i < pipe_s.nb_of_forks)
		waitpid(pipe_s.pid[i], NULL, 0);
	
}
