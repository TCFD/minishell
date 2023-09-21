/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:57:10 by wolf              #+#    #+#             */
/*   Updated: 2023/09/21 20:57:40 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	end_of_execve(pid_t pid, char *cmd_name)
{
	int			status;

	update_sign_ctrl(1);
	waitpid(pid, &status, 0);
	signal(SIGQUIT, SIG_IGN);
	update_sign_ctrl(0);
	if (WIFEXITED(status))
	{
		errno = WEXITSTATUS(status);
		update_err_code((int)errno);
	}
	else if (WIFSIGNALED(status))
		update_err_code(verif_signal(status, cmd_name));
	return (1);
}

int	run_execve(t_cmd_and_opt *cmdopt)
{
	pid_t		pid;

	errno = 0;
	pid = fork();
	signal(SIGQUIT, sig_handler);
	if (pid == -1)
		return ((void)update_err_code((int)errno),
			perror("fork"), exit(EXIT_FAILURE), 1);
	else if (pid == 0)
	{
		if (execve(cmdopt->command_path, cmdopt->opt_ty_tb.tab, get_env())
			== -1)
			ft_printf("Minishell : \033[31m%s\033[0m : %s\n", cmdopt->command_name,
				strerror(errno));
		free_everything(cmdopt, true);
		exit(errno);
	}
	return (end_of_execve(pid, cmdopt->command_name));
}

int	cmp(char *cmd_name, char *cmd_name_2)
{
	if (ft_strncmp(cmd_name, cmd_name_2, ft_strlen(cmd_name_2)) == 0
		&& ft_strlen(cmd_name) == ft_strlen(cmd_name_2))
		return (1);
	return (0);
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
	else if (!ft_strchr(cmdopt->command_path, '/'))
		return (ft_printf("\033[31m%s\033[0m : command not found\n",
				cmdopt->command_name), free_cmdopt(cmdopt),
			update_err_code(127), 1);
	else
	{
		if (!run_execve(cmdopt))
			return (0);
	}
	return (1);
}

int	execute_command(t_cmd_and_opt *cmdopt)
{
	t_redirections	redirections;
	bool			redir_out_bool;
	bool			redir_in_bool;
	bool			does_cmd_exist;

	does_cmd_exist = is_there_a_command(cmdopt->opt_ty_tb);
	if (!cmdopt->command_name)
		return (1);
	if (search_in_redirections(cmdopt, &redirections, &redir_in_bool) == 0)
		return (free_cmdopt(cmdopt), 1);
	if (search_out_redirections(cmdopt, &redirections, &redir_out_bool) == 0)
		return (free_cmdopt(cmdopt), 1);
	if (does_cmd_exist)
	{
		free(cmdopt->opt_ty_tb.tab[0]);
		cmdopt->opt_ty_tb.tab[0] = ft_strdup(cmdopt->command_name);
		if (!find_command(cmdopt))
			return (0);
	}
	ft_printf("\n");
	if (redir_in_bool)
		restore_stdin(&redirections);
	if (redir_out_bool)
		restore_stdout(redirections.stdout_save, redirections.file_out_fd);
	return (1);
}
