/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:14:17 by wolf              #+#    #+#             */
/*   Updated: 2023/09/25 17:00:52 by rciaze           ###   ########.fr       */
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

void launch_heredoc(t_cmd_and_opt *cmdopt)
{
	int		i;
	char	*filename;

	i = -1;
	while (cmdopt->opt_ty_tb.tab[++i])
	{
		if (ft_strnstr(cmdopt->opt_ty_tb.tab[i], D_L_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i])) && cmdopt->opt_ty_tb.type[i]
			!= SIMPLE_Q && cmdopt->opt_ty_tb.type[i] != DOUBLE_Q)
		{
			free(cmdopt->opt_ty_tb.tab[i]);
			cmdopt->opt_ty_tb.tab[i] = ft_strdup("<");
			i++;
			temp_heredoc(cmdopt->opt_ty_tb.tab[i], &filename);
			free(cmdopt->opt_ty_tb.tab[i]);
			cmdopt->opt_ty_tb.tab[i] = ft_strdup(filename);
			free(filename);
		}
	}
}

void	launch_pipex(t_cmd_and_opt *cmdopt)
{
	t_pipe			pipe_s;
	int				i;

	//Les pipes n'aimes pas trop qu'on fasse un heredoc dedans.
	//Donc, on les fait avant de lancer les pipes.
	//Pour quand meme avoir acces au donnes, on stock les fichiers dans un tableau.
	//On supprime tous ces fichiers a la fin de l'execution des pipes.
	launch_heredoc(cmdopt);
	init_pipex(&pipe_s, cmdopt);
	first_child(&pipe_s);
	n_child(&pipe_s, &i);
	last_child(&pipe_s, &i);
	close_all_pipes(&pipe_s);
	i = -1;
	int	status;
	while (++i < pipe_s.nb_of_forks)
		waitpid(pipe_s.pid[i], &status, 0);
	if (WIFEXITED(status))
	{
		errno = WEXITSTATUS(status);
		update_err_code((int)errno);
	}
	else if (WIFSIGNALED(status))
		update_err_code(verif_signal(status, pipe_s.cmdopt_tab[i]->opt_ty_tb.tab[0]));
	free_pipe(&pipe_s);
}
