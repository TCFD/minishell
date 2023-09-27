/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:39:21 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/27 10:53:47 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	add_rest(char **tab, char *type, int i, t_redirections *redir)
{
	int	w_case;

	if (ft_strncmp(tab[i], D_R_RAFTER, 2) == 0)
		w_case = 2;
	else
		w_case = 1;
	if (redirect_output(tab + i, &redir->stdout_save,
			&redir->file_out_fd, w_case))
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

int	open_sub_file(char **tab, int *i, int *funct_counter)
{
	int	fd;

	if (ft_strncmp(tab[*i], D_R_RAFTER, 2) == 0)
		fd = open(tab[*i + 1], O_CREAT | O_APPEND, 0666);
	else
		fd = open(tab[*i + 1], O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (update_err_code(errno), (void)ft_printf(2, "Minishell : %s: "
				, tab[1]), perror(""), 1);
	if (close(fd) == -1)
		return (perror("Failed to close file"), 0);
	*i += 1;
	*funct_counter += 1;
	return (1);
}

int	remove_redirections(char **tab, char *type, t_redirections *redir)
{
	int		i;
	int		funct_counter;
	char	*tmp;

	i = -1;
	funct_counter = 1;
	while (tab[++i])
	{
		tmp = ft_strnstr(tab[i], S_R_RAFTER, ft_strlen(tab[i]));
		if (tmp && type[i] != SIMPLE_Q && type[i] != DOUBLE_Q
			&& funct_counter < redir->counter)
		{
			if (open_sub_file(tab, &i, &funct_counter) == 0)
				return (0);
			continue ;
		}
		else if (tmp && type[i] != SIMPLE_Q && type[i] != DOUBLE_Q
			&& funct_counter == redir->counter)
			return (add_rest(tab, type, i, redir));
		if (redir->list)
			ft_lstadd_back(&redir->list, ft_lstnew(ft_strdup(tab[i]), type[i]));
		else
			redir->list = ft_lstnew(ft_strdup(tab[i]), type[i]);
	}
	return (add_rest(tab, type, i, redir));
}

void	redo_path_and_name(t_cmd_and_opt *cmd)
{
	free(cmd->command_name);
	free(cmd->command_path);
	if (cmd->path_unset == 0 && !ft_getenv("PATH"))
	{
		cmd->command_name = create_path(ft_strdup(cmd->opt_ty_tb.tab[0]), 0);
		cmd->command_path = ft_cpy(cmd->command_name, 0);
	}
	else
	{
		cmd->command_name = ft_strdup(cmd->opt_ty_tb.tab[0]);
		cmd->command_path = create_path(ft_strdup(cmd->opt_ty_tb.tab[0]), 1);
	}
}

int	search_out_redirections(t_cmd_and_opt *cmdopt, t_redirections *redir,
	bool *redir_bool)
{
	redir->counter = count_out_redirs(cmdopt->opt_ty_tb.tab,
			cmdopt->opt_ty_tb.type);
	if (redir->counter == 0)
	{
		*redir_bool = false;
		return (1);
	}
	else
		*redir_bool = true;
	redir->list = NULL;
	if (remove_redirections(cmdopt->opt_ty_tb.tab,
			cmdopt->opt_ty_tb.type, redir) == 0)
		return (ft_lstclear(&redir->list), 0);
	free_d_array(cmdopt->opt_ty_tb.tab);
	cmdopt->opt_ty_tb.tab = list_to_d_tab(redir->list);
	redo_path_and_name(cmdopt);
	ft_lstclear(&redir->list);
	return (1);
}
