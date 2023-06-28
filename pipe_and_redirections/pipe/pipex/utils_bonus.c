/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:06:29 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 16:16:34 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_paths(t_struct *my_s)
{
	int		i;
	char	*final_path;

	if (access(my_s->command[0], F_OK) == 0
		&& access(my_s->command[0], X_OK) == 0)
		return (0);
	i = -1;
	while (my_s->paths[++i])
	{
		final_path = ft_strjoin(my_s->paths[i], my_s->command[0]);
		if (access(final_path, F_OK) == 0 && access(final_path, X_OK) == 0)
			return (free(final_path), i);
		free(final_path);
	}
	final_path = ft_substr(my_s->command[0], 0, ft_strlen(my_s->command[0]));
	if (access(final_path, F_OK) == 0 && access(final_path, X_OK) < 0
		&& !ft_strncmp(final_path, "./", 2))
		perror(final_path);
	else
		ft_printf("%s: command not found\n", my_s->command[0]);
	free_for_check_paths(final_path, my_s);
	return (0);
}

void	free_for_check_paths(char *final_path, t_struct *my_s)
{
	int	i;

	i = -1;
	while (my_s->paths[++i])
		free(my_s->paths[i]);
	i = -1;
	while (++i < my_s->nb_of_pipes)
		free(my_s->pipe_fd[i]);
	return (free(my_s->pid), free_child(my_s), free(final_path),
		free(my_s->pipe_fd), free(my_s->paths), free(my_s), exit(EXIT_FAILURE));
}

void	exec(t_struct *my_s, char **envp, int i)
{
	char	*final_path;
	int		j;

	j = -1;
	if (access(my_s->command[0], F_OK) == 0
		&& access(my_s->command[0], X_OK) == 0)
	{
		if (execve(my_s->command[0], my_s->command, envp))
		{
			while (++j > my_s->nb_of_pipes)
				free(my_s->pipe_fd[j]);
			return (free(my_s->pipe_fd), free(my_s));
		}
	}
	else
	{
		final_path = ft_strjoin(my_s->paths[i], my_s->command[0]);
		if (execve(final_path, my_s->command, envp))
		{
			while (++j > my_s->nb_of_pipes)
				free(my_s->pipe_fd[j]);
			return (free(final_path), free(my_s->pipe_fd), free(my_s));
		}
	}
}

void	close_all_pipes(t_struct *my_struct)
{
	int	i;

	i = -1;
	while (++i < my_struct->nb_of_pipes)
	{
		close(my_struct->pipe_fd[i][0]);
		close(my_struct->pipe_fd[i][1]);
	}
}

void	free_child(t_struct *my_struct)
{
	int	i;

	i = -1;
	while (my_struct->command[++i])
		free(my_struct->command[i]);
	free(my_struct->command);
}
