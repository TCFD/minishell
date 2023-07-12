/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_rafter_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:01:23 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/12 15:03:37 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_stdin(int stdin_save, int filefd)
{
	if (dup2(stdin_save, STDIN_FILENO) == -1)
		return (perror("Failed to restore stdin"));
	close(filefd);
	close(stdin_save);
}

int	redirect_input(char **tab, int *stdin_save, int *filefd)
{
	*stdin_save = dup(STDIN_FILENO);
	if (*stdin_save == -1)
		return (perror("Failed to save stdin"), 1);
	*filefd = open(tab[1], O_RDONLY, 0666);
	if (*filefd == -1)
		return (perror("Minishell : "), 1);
	if (dup2(*filefd, STDIN_FILENO) == -1)
		return (perror("Failed to redirect stdin"), 1);
	return (0);
}
