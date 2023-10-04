/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:24:53 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 14:27:58 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_command_and_option	t_cmd_and_opt;
typedef struct s_pipe				t_pipe;
typedef void (*f_func);

void	ft_exit_pipex(int code, bool msg);

#endif