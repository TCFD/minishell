/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:33:30 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 17:05:23 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	path_is_unset(t_struct *my_struct)
{
	if (access(my_struct->command[0], F_OK) == 0
		&& access(my_struct->command[0], X_OK) == 0)
		return (0);
	else
	{
		ft_putstr_fd(my_struct->command[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		return (free_child(my_struct), free(my_struct), exit(EXIT_FAILURE), 0);
	}
}

void	f_child1(t_struct *my_struct, char **argv, char **envp)
{
	int	i;

	my_struct->file = open(argv[1], O_RDONLY);
	if (my_struct->file < 0)
	{
		i = -1;
		while (my_struct->paths && my_struct->paths[++i])
			free(my_struct->paths[i]);
		return (perror(argv[1]), free(my_struct->paths),
			free(my_struct), exit(EXIT_FAILURE));
	}
	dup2(my_struct->file, STDIN_FILENO);
	dup2(my_struct->pipe_fd[1], STDOUT_FILENO);
	close (my_struct->pipe_fd[0]);
	my_struct->command = ft_split(argv[2], ' ');
	if (my_struct->unset_path == false)
		i = check_paths(my_struct);
	else
		i = path_is_unset(my_struct);
	exec(my_struct, envp, i);
	free_child(my_struct);
}

void	f_child2(t_struct *my_struct, char **argv, char **envp)
{
	int	i;

	my_struct->file = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (my_struct->file < 0)
	{
		i = -1;
		while (my_struct->paths && my_struct->paths[++i])
			free(my_struct->paths[i]);
		return (perror(argv[4]), free(my_struct->paths),
			free(my_struct), exit(EXIT_FAILURE));
	}	
	dup2(my_struct->pipe_fd[0], STDIN_FILENO);
	dup2(my_struct->file, STDOUT_FILENO);
	close (my_struct->pipe_fd[1]);
	my_struct->command = ft_split(argv[3], ' ');
	if (my_struct->unset_path == false)
		i = check_paths(my_struct);
	else
		i = path_is_unset(my_struct);
	exec(my_struct, envp, i);
	free_child(my_struct);
}

void	free_child(t_struct *my_struct)
{
	int	i;

	i = -1;
	while (my_struct->command[++i])
		free(my_struct->command[i]);
	free(my_struct->command);
}

void	exec(t_struct *my_struct, char **envp, int i)
{
	char	*final_path;

	if (access(my_struct->command[0], F_OK) == 0
		&& access(my_struct->command[0], X_OK) == 0)
	{
		if (execve(my_struct->command[0], my_struct->command, envp))
			return (free(my_struct));
	}
	else
	{
		final_path = ft_strjoin(my_struct->paths[i], my_struct->command[0]);
		if (execve(final_path, my_struct->command, envp))
			return (free(final_path), free(my_struct));
	}
}
