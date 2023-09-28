/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:24:53 by wolf              #+#    #+#             */
/*   Updated: 2023/09/27 13:46:48 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_command_and_option	t_cmd_and_opt;
typedef struct s_pipe				t_pipe;
typedef void (*f_func);

typedef struct c_fork_opt
{
	t_cmd_and_opt	*cmdopt;
	char			**str;
	int				cmd_id;
}t_fork_opt;

void	ft_exit_pipex(t_pipe *pipe_s, int code, bool msg);
void	init_fork_opt(t_fork_opt *fork_utils);
void	free_fork_opt(t_fork_opt *fork_utils);
void	execute_pipex(char **lst_cmd);

#endif