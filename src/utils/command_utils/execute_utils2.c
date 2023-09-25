/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:42:15 by wolf              #+#    #+#             */
/*   Updated: 2023/09/25 16:44:40 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*read_bytes(int *fd)
{
	ssize_t	bytes_read;
	char	buffer[1024];

	bytes_read = read(fd[0], buffer, sizeof(buffer));
	if (bytes_read == -1)
		exit(EXIT_FAILURE);
	buffer[bytes_read - 1] = '\0';
	close(fd[0]);
	close(fd[1]);
	return (ft_strdup(buffer));
}

char	*get_execve_return(t_cmd_and_opt *cmdopt)
{
	pid_t	pid;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		return ((void)update_err_code((int)errno), exit(EXIT_FAILURE), NULL);
	pid = fork();
	if (pid == -1)
		return ((void)update_err_code((int)errno), exit(EXIT_FAILURE), NULL);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve(cmdopt->command_path, cmdopt->opt_ty_tb.tab, get_env())
			== -1)
			return ((void)update_err_code((int)errno), exit(EXIT_FAILURE),
				NULL);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		return (read_bytes(pipefd));
	}
	return (NULL);
}

bool	is_there_a_command(t_opt_tab opt)
{
	int	i;

	if (!opt.tab)
		return (false);
	i = 0;
	while (opt.tab[i])
	{
		if ((opt.tab[i][0] == '>' || opt.tab[i][0] == '<')
			&& opt.type[i] != SIMPLE_Q && opt.type[i] != DOUBLE_Q)
			i++;
		else
			return (true);
		if (opt.tab[i])
			i++;
	}
	return (false);
}

int	verif_signal(int status, char *cmd_name)
{
	int	signal_code;

	signal_code = WTERMSIG(status);
	if (signal_code == SIGSEGV)
		return (
			ft_printf(2, "Minishell: Segmentation fault [%s]\n", cmd_name), 139);
	else
	{
		if (signal_code != 2 && signal_code != 3)
			return (ft_printf(2, "\nMinishell: Process completed\n"), 143);
	}
	if (signal_code == 2)
		return (130);
	if (signal_code == 3)
		return (131);
	return (errno);
}

int	go_to_cmd(t_cmd_and_opt *cmdopt)
{
	int	f_cmd;

	f_cmd = find_command(cmdopt);
	if (f_cmd < 0)
		return (0);
	if (f_cmd != 0)
		change_underscore_value(cmdopt, false);
	return (1);
}
