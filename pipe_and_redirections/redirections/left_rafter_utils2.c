/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_rafter_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:01:23 by rciaze            #+#    #+#             */
/*   Updated: 2023/08/23 11:02:33 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_stdin(t_redirections *redir)
{
	if (dup2(redir->stdin_save, STDIN_FILENO) == -1)
		return (perror("Failed to restore stdin"));
	close(redir->file_in_fd);
	close(redir->stdin_save);
	if (redir->heredoc)
	{
		unlink(redir->random_adress);
		free(redir->random_adress);
	}
}

void	temp_heredoc(char *str, char **random_adress)
{
	int			fd;
	long int	random;
	char		*line;

	random = (long int)random_adress;
	*random_adress = ft_itoa(random);
	*random_adress = ft_join(ft_strdup("/tmp/"), *random_adress);
	fd = open(*random_adress, O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, str, ft_strlen(str)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

int	redirect_input(char **tab, int *stdin_save, int *filefd, char **random_adress)
{
	*stdin_save = dup(STDIN_FILENO);
	if (*stdin_save == -1)
		return (perror("Failed to save stdin"), 1);
	if (ft_strnstr(tab[0], D_L_RAFTER, ft_strlen(tab[0])))
	{
		temp_heredoc(tab[1], random_adress);
		*filefd = open(*random_adress, O_RDONLY, 0666);
	}
	else
		*filefd = open(tab[1], O_RDONLY, 0666);
	if (*filefd == -1)
		return (perror("Minishell : "), 1);
	if (dup2(*filefd, STDIN_FILENO) == -1)
		return (perror("Failed to redirect stdin"), 1);
	return (0);
}
