/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:14:17 by wolf              #+#    #+#             */
/*   Updated: 2023/09/22 22:31:45 by zbp15            ###   ########.fr       */
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

void	launch_pipex(t_cmd_and_opt *cmdopt)
{
	t_pipe			pipe_s;
	int				i;

	init_pipex(&pipe_s, cmdopt);
	first_child(&pipe_s);
	n_child(&pipe_s, &i);
	last_child(&pipe_s, &i);
	close_all_pipes(&pipe_s);
	i = -1;
	while (++i < pipe_s.nb_of_forks)
		waitpid(pipe_s.pid[i], NULL, 0);
	free_pipe(&pipe_s);
}
