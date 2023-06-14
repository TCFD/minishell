/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:12:48 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 16:08:54 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_struct *my_struct, char **argv, char **envp)
{
	int	child1;
	int	child2;

	child1 = fork();
	if (child1 < 0)
		return (perror(NULL));
	else if (child1 == 0)
		f_child1(my_struct, argv, envp);
	child2 = fork();
	if (child2 < 0)
		return (perror(NULL));
	else if (!child2)
		f_child2(my_struct, argv, envp);
	close (my_struct->pipe_fd[0]);
	close (my_struct->pipe_fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return ;
}

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
	i = -1;
	while (my_s->paths[++i])
		free(my_s->paths[i]);
	return (free_child(my_s), free(final_path), free(my_s->paths),
		free(my_s), exit(EXIT_FAILURE), 0);
}
