/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:12:00 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/14 17:08:05 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_struct
{
	int		file;
	bool	unset_path;
	int		**pipe_fd;
	int		nb_of_pipes;
	int		nb_of_forks;
	int		*pid;
	char	**paths;
	char	**command;
}	t_struct;

void	pipex(t_struct *my_struct, char **argv, char **envp, int argc);
void	pipex2(t_struct *my_struct, char **argv, char **envp, int argc);
void	f_child1(t_struct *my_struct, char **argv, char **envp);
void	last_child(t_struct *my_struct, char **argv, char **envp, int i);
void	nb_child(t_struct *my_struct, char **argv, char **envp, int i);
char	**get_path(char **envp, t_struct *my_s, int i);
void	free_child(t_struct *my_struct);
void	exec(t_struct *my_s, char **envp, int i);
int		check_paths(t_struct *my_struct);
void	free_for_check_paths(char *final_path, t_struct *my_s);
void	close_all_pipes(t_struct *my_struct);
void	malloc_and_pipe(t_struct *my_struct, int i);
void	pipex_heredoc(t_struct *my_struct, char **argv, char **envp, int argc);
void	first_child_heredoc(t_struct *my_s, char **argv, char **envp, int i);
void	get_usr_input(t_struct *my_struct, char **argv);
int		path_is_unset(t_struct *my_struct);
#endif