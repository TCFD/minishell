/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:22:53 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 17:05:06 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_struct	*my_s;
	int			i;

	if (ac < 5 || (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) && ac > 6))
		return (ft_printf("Mauvaise utilisation.\n"));
	my_s = ft_calloc(sizeof(t_struct), 1);
	if (!my_s)
		return (0);
	my_s->nb_of_pipes = ac - 4;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		my_s->nb_of_pipes = 1;
	malloc_and_pipe(my_s, -1);
	my_s->paths = get_path(envp, my_s, 0);
	pipex(my_s, av, envp, ac);
	if (my_s->unset_path == false)
	{
		i = -1;
		while (my_s->paths[++i])
			free(my_s->paths[i]);
		free(my_s->paths);
	}
	i = -1;
	while (++i < my_s->nb_of_pipes)
		free(my_s->pipe_fd[i]);
	return (free(my_s->pipe_fd), free(my_s), 0);
}

void	malloc_and_pipe(t_struct *my_s, int i)
{
	my_s->pipe_fd = malloc(sizeof(int [2]) * my_s->nb_of_pipes);
	if (!my_s->pipe_fd)
		return (free(my_s), exit(0));
	while (++i < my_s->nb_of_pipes)
	{
		my_s->pipe_fd[i] = ft_calloc(sizeof(int), 2);
		if (my_s->pipe_fd[i] == NULL)
		{
			i++;
			while (--i > -1)
				free(my_s->pipe_fd[i]);
			free(my_s->pipe_fd);
			free(my_s);
			exit(EXIT_FAILURE);
		}
		else if (pipe(my_s->pipe_fd[i]) < 0)
		{
			i++;
			while (--i > -1)
				free(my_s->pipe_fd[i]);
			free(my_s->pipe_fd);
			free(my_s);
			exit(EXIT_FAILURE);
		}
	}
}

char	**get_path(char **envp, t_struct *my_s, int i)
{
	char	**paths;
	char	*temp_path;

	my_s->unset_path = false;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
	{
		my_s->unset_path = true;
		paths = NULL;
	}
	else
	{
		paths = ft_split(envp[i] + 5, ':');
		i = -1;
		while (paths[++i])
		{
			temp_path = ft_strjoin(paths[i], "/");
			free(paths[i]);
			paths[i] = ft_strdup(temp_path);
			free(temp_path);
		}
	}
	return (paths);
}
