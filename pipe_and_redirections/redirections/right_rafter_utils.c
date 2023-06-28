/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:39:21 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/28 15:40:43 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_output(char **tab, int *stdout_save, int *filefd, int which_case)
{
	int			i;

	*stdout_save = dup(STDOUT_FILENO);
	if (*stdout_save == -1)
		return (perror("Failed to save stdout"), 1);
	printf("file = %s\n, case = %d,\n", tab[1], which_case);
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

int	search_redirections(t_cmd_and_opt *cmdopt, int *stdout_save,
	int *filefd, long int *position)
{
	*position = search_d_tab(cmdopt->opt_tab, ">>");
	if (*position > -1)
		if (redirect_output(cmdopt->opt_tab + *position, stdout_save,
				filefd, 2))
			return (1);
	if (*position <= -1)
	{
		*position = search_d_tab(cmdopt->opt_tab, ">");
		if (*position > -1)
			if (redirect_output(cmdopt->opt_tab + *position, stdout_save,
					filefd, 1))
				return (1);
	}	
	printf("position %ld\n", *position);
	return (0);
}