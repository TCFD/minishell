/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:37:54 by zbp15             #+#    #+#             */
/*   Updated: 2023/10/06 15:43:06 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	redirect_output(char **tab, int *stdout_save, int *filefd, int which_case)
{
	if (which_case == 1)
		*filefd = open(tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		*filefd = open(tab[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (*filefd == -1)
		return (update_err_code(errno),
			(void)ft_printf(2, "Minishell : %s: ", tab[1]), perror(""), 1);
	*stdout_save = dup(STDOUT_FILENO);
	if (*stdout_save == -1)
		return (perror("Failed to save stdout"), 1);
	if (dup2(*filefd, STDOUT_FILENO) == -1)
		return (perror("Failed to redirect stdout"), 1);
	return (0);
}

void	restore_stdout(int stdout_save, int filefd)
{
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		return (perror("Failed to restore stdout"));
	if (close(filefd) == -1)
		return (perror("Failed to close file"));
	close(stdout_save);
}

char	**list_to_d_tab(t_list *list)
{
	int		i;
	char	**tab;
	int		size;

	size = ft_lstsize(list);
	tab = ft_calloc(size + 1, sizeof(char *));
	if (!tab)
		return (malloc_failure(), NULL);
	i = 0;
	while (list)
	{
		tab[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	count_out_redirs(char **tab, char *type)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (tab[++i])
		if (ft_strnstr(tab[i], S_R_RAFTER, ft_strlen(tab[i]))
			&& type[i] != SIMPLE_Q && type[i] != DOUBLE_Q)
			counter++;
	return (counter);
}

void	redo_path_and_name(t_cmd_and_opt *cmd)
{
	if (cmd->path_unset == 0 && !ft_getenv("PATH"))
	{
		cmd->command_name = create_path(cmd->opt_ty_tb.tab[0], 0);
		cmd->command_path = ft_cpy(cmd->command_name, 0);
	}
	else
	{
		cmd->command_name = ft_strdup(cmd->opt_ty_tb.tab[0]);
		cmd->command_path = create_path(cmd->opt_ty_tb.tab[0], 1);
	}
}
