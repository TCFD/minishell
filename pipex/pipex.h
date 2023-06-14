/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:12:00 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 16:09:01 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_struct
{
	int		file;
	bool	unset_path;
	int		pipe_fd[2];
	char	**paths;
	char	**command;
}	t_struct;

void	exec(t_struct *my_struct, char **envp, int i);
int		check_paths(t_struct *my_s);
void	pipex(t_struct *my_struct, char **argv, char **envp);
void	f_child1(t_struct *my_struct, char **argv, char **envp);
void	f_child2(t_struct *my_struct, char **argv, char **envp);
void	free_child(t_struct *my_struct);
char	**get_path(char **envp, t_struct *my_struct);

#endif