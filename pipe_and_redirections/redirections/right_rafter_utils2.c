/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:37:54 by zbp15             #+#    #+#             */
/*   Updated: 2023/07/12 13:00:31 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_output(char **tab, int *stdout_save, int *filefd, int which_case)
{
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
	return (0);
}

void	restore_stdout(int stdout_save, int filefd)
{
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		return (perror("Failed to restore stdout"));
	close(filefd);
	close(stdout_save);
}

char	**list_to_d_tab(t_list *list)
{
	int		i;
	char	**tab;

	tab = ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
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
		if (ft_strnstr(tab[i], SIMPLE_R_RAFTER, ft_strlen(tab[i]))
			&& type[i] != SIMPLE_Q && type[i] != DOUBLE_Q)
			counter++;
	return (counter);
}
