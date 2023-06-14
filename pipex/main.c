/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:08:45 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 16:56:47 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	*my_struct;
	int			i;

	if (argc < 5)
		return (ft_printf("Trop peu d'arguments !\n"));
	if (argc > 5)
		return (ft_printf("Trop d'arguments !\n"));
	my_struct = ft_calloc(sizeof(t_struct), 1);
	if (!my_struct || pipe(my_struct->pipe_fd) != 0)
		return (0);
	my_struct->unset_path = false;
	my_struct->paths = get_path(envp, my_struct);
	pipex(my_struct, argv, envp);
	if (my_struct->unset_path == false)
	{
		i = -1;
		while (my_struct->paths[++i])
			free(my_struct->paths[i]);
		free(my_struct->paths);
	}
	free(my_struct);
	return (0);
}

char	**get_path(char **envp, t_struct *my_struct)
{
	char	**paths;
	char	*temp_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
	{
		my_struct->unset_path = true;
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
