/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:57:10 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 16:57:30 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	end_of_execve(pid_t pid, char *cmd_name)
{
	int			status;

	update_sign_ctrl(1);
	waitpid(pid, &status, 0);
	update_sign_ctrl(0);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(status))
	{
		errno = WEXITSTATUS(status);
		if (cmp(cmd_name, "./minishell"))
			return (update_err_code_force(errno, true), 1);
		update_err_code((int)errno);
	}
	else if (WIFSIGNALED(status))
		update_err_code(verif_signal(status, cmd_name));
	return (1);
}

int	execve_child(t_cmd_and_opt *cmdopt, pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		return ((void)update_err_code((int)errno),
			perror("fork"), exit(EXIT_FAILURE), 1);
	else if (*pid == 0)
	{
		if (execve(cmdopt->command_path, cmdopt->opt_ty_tb.tab, get_env())
			== -1)
			ft_printf(2, "Minishell : \001\e[31m\002%s\001\e[0m\002 : %s\n",
				cmdopt->command_name, strerror(errno));
		ft_exit(errno, true);
	}
	return (0);
}

int	run_execve(t_cmd_and_opt *cmdopt)
{
	pid_t		pid;

	errno = 0;
	signal(SIGQUIT, sig_handler);
	if (!cmdopt->is_child)
	{
		if (execve_child(cmdopt, &pid))
			return (1);
	}
	else
	{
		if (execve(cmdopt->command_path, cmdopt->opt_ty_tb.tab, get_env())
			== -1)
		{
			ft_printf(2, "Minishell : \001\e[31m\002%s\001\e[0m\002 : %s\n",
				cmdopt->command_name, strerror(errno));
			return (1);
		}
	}
	return (end_of_execve(pid, cmdopt->command_name));
}

int	find_command(t_cmd_and_opt *cmdopt)
{
	if (cmp(cmdopt->command_name, "cd"))
		cd_remake(cmdopt);
	else if (cmp(cmdopt->command_name, "echo"))
		echo_remake(cmdopt);
	else if (cmp(cmdopt->command_name, "unset"))
		unset_all_env_var(cmdopt);
	else if (verif_if_env_called(cmdopt) && !cmdopt->opt_ty_tb.tab[1])
		display_env(get_env(), cmdopt);
	else if (cmp(cmdopt->command_name, "export"))
		export_all_var(cmdopt);
	else if (cmp(cmdopt->command_name, "pwd"))
		print_pwd();
	else if (cmp(cmdopt->command_name, "exit"))
		check_exit(cmdopt);
	else if (!ft_strchr(cmdopt->command_path, '/'))
		return (ft_printf(2, "Minishell : \001\e[31m\002%s\001\e[0m\002 : "
				"command not found\n", cmdopt->command_name),
			change_underscore_value(cmdopt, false), update_err_code(127), 0);
	else
		if (!run_execve(cmdopt))
			return (-1);
	return (1);
}

int	execute_command(t_cmd_and_opt *cmdopt)
{
	t_redirections	redirections;
	bool			redir_out_bool;
	bool			redir_in_bool;

	if (!cmdopt->command_name)
		return (1);
	if (search_in_redirections(cmdopt, &redirections, &redir_in_bool) == 0)
		return (1);
	if (search_out_redirections(cmdopt, &redirections, &redir_out_bool) == 0)
		return (1);
	if (is_there_a_command(cmdopt->opt_ty_tb))
	{
		if (!cmd_exist(cmdopt))
			return (0);
	}
	else
		change_underscore_value_void(false);
	if (redir_in_bool)
		restore_stdin(&redirections);
	if (redir_out_bool)
		restore_stdout(redirections.stdout_save, redirections.file_out_fd);
	return (1);
}
