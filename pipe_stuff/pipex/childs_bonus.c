/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:22:55 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 17:07:51 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	path_is_unset(t_struct *my_s)
{
	if (access(my_s->command[0], F_OK) == 0
		&& access(my_s->command[0], X_OK) == 0)
		return (0);
	else
	{
		ft_putstr_fd(my_s->command[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		return (free_child(my_s), free(my_s), exit(EXIT_FAILURE), 0);
	}
}

void	f_child1(t_struct *my_s, char **argv, char **envp)
{
	int	i;

	my_s->file = open(argv[1], O_RDONLY);
	if (my_s->file < 0)
	{
		i = -1;
		while (my_s->paths && my_s->paths[++i])
			free(my_s->paths[i]);
		return (perror(argv[1]), free(my_s->paths),
			free(my_s), exit(EXIT_FAILURE));
	}
	dup2(my_s->file, STDIN_FILENO);
	dup2(my_s->pipe_fd[0][1], STDOUT_FILENO);
	close_all_pipes(my_s);
	my_s->command = ft_split(argv[2], ' ');
	if (my_s->unset_path == false)
		i = check_paths(my_s);
	else
		i = path_is_unset(my_s);
	exec(my_s, envp, i);
	free_child(my_s);
}

void	first_child_heredoc(t_struct *my_s, char **argv, char **envp, int i)
{
	my_s->file = open("temp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (my_s->file < 0)
	{
		i = -1;
		while (my_s->paths && my_s->paths[++i])
			free(my_s->paths[i]);
		return (perror(argv[1]), free(my_s->paths),
			free(my_s), exit(EXIT_FAILURE));
	}
	get_usr_input(my_s, argv);
	if (close(my_s->file))
		return (perror(argv[1]), exit(EXIT_FAILURE));
	my_s->file = open("temp", O_RDONLY);
	if (my_s->file < 0)
		return (perror(argv[1]), exit(EXIT_FAILURE));
	dup2(my_s->file, STDIN_FILENO);
	dup2(my_s->pipe_fd[0][1], STDOUT_FILENO);
	close_all_pipes(my_s);
	my_s->command = ft_split(argv[3], ' ');
	if (my_s->unset_path == false)
		i = check_paths(my_s);
	else
		i = path_is_unset(my_s);
	return (exec(my_s, envp, i), free_child(my_s));
}

void	get_usr_input(t_struct *my_s, char **argv)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, argv[2], 1))
		{
			write(my_s->file, line, ft_strlen(line));
			free (line);
			line = get_next_line(STDIN_FILENO);
		}
		else
			break ;
	}
	free (line);
}

void	nb_child(t_struct *my_s, char **argv, char **envp, int i)
{
	int	j;

	my_s->command = ft_split(argv[i + 3], ' ');
	dup2(my_s->pipe_fd[i + 1][1], STDOUT_FILENO);
	close_all_pipes(my_s);
	dup2(my_s->pipe_fd[i][0], STDIN_FILENO);
	if (my_s->unset_path == false)
		j = check_paths(my_s);
	else
		j = path_is_unset(my_s);
	exec(my_s, envp, j);
	free_child(my_s);
}
