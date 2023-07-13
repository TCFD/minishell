/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_rafter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:26:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/13 17:03:19 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_rest_in(char **tab, char *type, int i, t_redirections *redir)
{
	if (redirect_input(tab + i, &redir->stdin_save, &redir->file_in_fd))
		return (0);
	if (!tab[i + 2])
		return (1);
	i += 2;
	while (tab[i])
	{
		if (redir->list)
			ft_lstadd_back(&redir->list, ft_lstnew(ft_strdup(tab[i]), type[i]));
		else
			redir->list = ft_lstnew(ft_strdup(tab[i]), type[i]);
		i++;
	}
	return (1);
}

int	remove_in_redirections(char **tab, char *type, t_redirections *redir)
{
	int		i;
	int		funct_counter;
	char	*tmp;

	i = -1;
	funct_counter = 1;
	while (tab[++i])
	{
		tmp = ft_strnstr(tab[i], S_L_RAFTER, ft_strlen(tab[i]));
		if (tmp && type[i] != SIMPLE_Q && type[i] != DOUBLE_Q
			&& funct_counter < redir->counter)
		{
			if (ft_strnstr(tab[i], D_L_RAFTER, ft_strlen(tab[i])))
				temp_heredoc(tab[i + 1]);
			i++;
			funct_counter++;
			continue ;
		}
		else if (tmp && type[i] != SIMPLE_Q && type[i] != DOUBLE_Q
			&& funct_counter == redir->counter)
			return (add_rest_in(tab, type, i, redir));
		if (redir->list)
			ft_lstadd_back(&redir->list, ft_lstnew(ft_strdup(tab[i]), type[i]));
		else
			redir->list = ft_lstnew(ft_strdup(tab[i]), type[i]);
	}
	return (add_rest_in(tab, type, i, redir));
}

int	count_in_redirs(char **tab, char *type, bool *heredoc)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (tab[++i])
	{
		if (ft_strnstr(tab[i], D_L_RAFTER, ft_strlen(tab[i]))
			&& type[i] != SIMPLE_Q && type[i] != DOUBLE_Q)
			*heredoc = true;
		if (ft_strnstr(tab[i], S_L_RAFTER, ft_strlen(tab[i]))
			&& type[i] != SIMPLE_Q && type[i] != DOUBLE_Q)
			counter++;
	}
	return (counter);
}

int	search_in_redirections(t_cmd_and_opt *cmdopt, t_redirections *redir,
	bool *redir_bool)
{
	redir->heredoc = false;
	redir->counter = count_in_redirs(cmdopt->opt_ty_tb.tab,
			cmdopt->opt_ty_tb.type, &redir->heredoc);
	if (redir->counter == 0)
	{
		*redir_bool = false;
		return (1);
	}
	else
		*redir_bool = true;
	redir->list = NULL;
	if (remove_in_redirections(cmdopt->opt_ty_tb.tab,
			cmdopt->opt_ty_tb.type, redir) == 0)
		return (0);
	free_d_array(cmdopt->opt_ty_tb.tab);
	cmdopt->opt_ty_tb.tab = list_to_d_tab(redir->list);
	return (1);
}
