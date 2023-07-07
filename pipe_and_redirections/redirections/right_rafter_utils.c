/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:39:21 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/07 15:44:50 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* int	redirect_output(char **tab, int *stdout_save, int *filefd, int which_case)
{
	int			i;

	*stdout_save = dup(STDOUT_FILENO);
	if (*stdout_save == -1)
		return (perror("Failed to save stdout"), 1);
	if (which_case == 1)
		*filefd = open(tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		*filefd = open(tab[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (*filefd == -1)
		return (perror("Failed to open file"), 1);
	if (dup2(*filefd, STDOUT_FILENO) == -1)
		return (perror("Failed to redirect stdout"), 1);
	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	return (0);
}

void	restore_fd(int position, int stdout_save, int filefd)
{
	if (position > -1)
	{
		if (dup2(stdout_save, STDOUT_FILENO) == -1)
			return (perror("Failed to restore stdout"));
		close(filefd);
		close(stdout_save);
	}
}

t_list	*remove_redirection(t_cmd_and_opt *cmdopt,  long int *position)
{
	int		i;
	int		fd;
	char	*last_one;
	t_list	**start;
	t_list	*return_list;

	i = -1;
	last_one = ft_strdup("");
	start = &return_list;
	while (cmdopt->opt_ty_tb.tab[++i])
	{
		if (cmdopt->opt_ty_tb.tab[i + 1] && cmdopt->opt_ty_tb.tab[i + 2]
			&& ft_strncmp(cmdopt->opt_ty_tb.tab[i], SIMPLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i]))
			|| ft_strncmp(cmdopt->opt_ty_tb.tab[i], DOUBLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i])))
		{
			fd = open(cmdopt->opt_ty_tb.tab[i + 1], O_CREAT, 0666);
			if (fd == -1)
				return (perror("minishell : "), NULL);
			if (close(fd) != 0)
				return (perror("minishell : "), NULL);
			*position = 1;
			i++;
		}
		else if (ft_strncmp(cmdopt->opt_ty_tb.tab[i], SIMPLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i]))
			|| ft_strncmp(cmdopt->opt_ty_tb.tab[i], DOUBLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i])))
		{
			free(last_one);
			last_one = ft_strdup(cmdopt->opt_ty_tb.tab[i]);
			*position = 1;
		}
		else
		{
			return_list = ft_lstnew(ft_strdup(cmdopt->opt_ty_tb.tab[i]), 0);
			return_list = return_list->next;
		}
	}
	return (*start);
}

char	**list_to_d_tab(t_list *list)
{
	int	i;
	char	**tab;
	
	tab = ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
	i = 0;
	while (list)
	{
		tab[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	return (tab);
}

int	search_redirections(t_cmd_and_opt *cmdopt, int *stdout_save,
	int *filefd, long int *position)
{
	t_list	*list;
	int		i;

	list = remove_redirection(cmdopt, position);
	free_d_array(cmdopt->opt_ty_tb.tab);
	cmdopt->opt_ty_tb.tab = list_to_d_tab(list);
	return (0);
}
 */