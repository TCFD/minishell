/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:44:30 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/02 15:33:21 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	g_error_code;

void	update_err_code(int code_err)
{
	if (code_err == 13)
		g_error_code = 126;
	else if (code_err == 22)
		g_error_code = 1;
	else if (code_err == 5 || code_err == 9
		|| code_err == 12 || code_err == 17
		|| code_err == 25)
		g_error_code = 127;
	else if (code_err == 32)
		g_error_code = 141;
	else if (code_err == 0)
		g_error_code = 0;
	else
		g_error_code = code_err;
}

void	update_err_code_force(int code_err, bool force)
{
	if (force)
	{
		g_error_code = code_err;
		return ;
	}
	return (update_err_code(code_err));
}

int	exit_code(int code)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("exit_code"), EXIT_FAILURE);
	if (pid == 0)
		ft_exit(code, false);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	update_err_code_pipe(int code_err, bool exit_pipe)
{
	if (exit_pipe == true)
	{
		g_error_code = exit_code(code_err);
		return ;
	}
	if (code_err == 13)
		g_error_code = 126;
	else if (code_err == 22)
		g_error_code = 1;
	else if (code_err == 5 || code_err == 9
		|| code_err == 12 || code_err == 17
		|| code_err == 25)
		g_error_code = 127;
	else if (code_err == 32)
		g_error_code = 141;
	else if (code_err == 0)
		g_error_code = 0;
	else
		g_error_code = code_err;
}
