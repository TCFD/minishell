/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:24:53 by wolf              #+#    #+#             */
/*   Updated: 2023/09/10 15:36:30 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdarg.h>
# define MK_CD_REMAKE 1
# define MK_ECHO_REMAKE 2
# define MK_UNSET_ALL_ENV_VAR 3
# define MK_DISPLAY_ENV 4
# define MK_EXPORT_ALL_VAR 5
# define MK_PRINT_PWD 6

typedef void (*f_func);
typedef struct s_command_and_option	t_cmd_and_opt;

typedef struct c_fork_opt
{
	t_cmd_and_opt	*cmdopt;
	char			**str;
	int				cmd_id;
}t_fork_opt;

void	init_fork_opt(t_fork_opt *fork_utils);
void	free_fork_opt(t_fork_opt *fork_utils);
void	execute_pipex(char **lst_cmd);

#endif