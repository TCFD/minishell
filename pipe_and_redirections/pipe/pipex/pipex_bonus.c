/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:22:56 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 17:07:38 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex(t_struct *my_s, char **argv, char **envp, int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		return (pipex_heredoc(my_s, argv, envp, argc));
	my_s->pid = ft_calloc(sizeof(int), argc - 3);
	my_s->nb_of_forks = argc - 5;
	my_s->pid[0] = fork();
	if (my_s->pid[0] < 0)
		return (perror(NULL));
	if (my_s->pid[0] == 0)
		f_child1(my_s, argv, envp);
	pipex2(my_s, argv, envp, argc);
}

void	pipex2(t_struct *my_s, char **argv, char **envp, int argc)
{
	int	i;

	i = 1;
	while (i < my_s->nb_of_forks + 1)
	{
		my_s->pid[i] = fork();
		if (my_s->pid[i] < 0)
			return (perror(NULL));
		if (my_s->pid[i] == 0)
			nb_child(my_s, argv, envp, i - 1);
		i++;
	}
	my_s->pid[i] = fork();
	if (my_s->pid[i] < 0)
		return (perror(NULL));
	if (my_s->pid[i] == 0)
		last_child(my_s, argv, envp, argc);
	close_all_pipes(my_s);
	i = -1;
	while (++i < my_s->nb_of_forks + 2)
		waitpid(my_s->pid[i], NULL, 0);
	free(my_s->pid);
}

void	pipex_heredoc(t_struct *my_s, char **argv, char **envp, int argc)
{
	int	child1;
	int	child2;

	child1 = fork();
	if (child1 < 0)
		return (perror(NULL));
	if (child1 == 0)
		first_child_heredoc(my_s, argv, envp, -1);
	waitpid(child1, NULL, 0);
	child2 = fork();
	if (child2 < 0)
		return (perror(NULL));
	else if (!child2)
		last_child(my_s, argv, envp, argc);
	close (my_s->pipe_fd[0][0]);
	close (my_s->pipe_fd[0][1]);
	waitpid(child2, NULL, 0);
	unlink("temp");
	return ;
}

void	last_child(t_struct *my_s, char **argv, char **envp, int argc)
{
	int	i;

	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		my_s->file = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		my_s->file = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (my_s->file < 0)
	{
		i = -1;
		while (my_s->paths && my_s->paths[++i])
			free(my_s->paths[i]);
		return (perror(argv[argc - 1]), free(my_s->paths),
			free(my_s), exit(EXIT_FAILURE));
	}
	dup2(my_s->pipe_fd[my_s->nb_of_pipes - 1][0], STDIN_FILENO);
	dup2(my_s->file, STDOUT_FILENO);
	close_all_pipes(my_s);
	my_s->command = ft_split(argv[argc - 2], ' ');
	if (my_s->unset_path == false)
		i = check_paths(my_s);
	else
		i = path_is_unset(my_s);
	exec(my_s, envp, i);
	free_child(my_s);
}
