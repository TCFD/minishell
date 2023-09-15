/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:14:17 by wolf              #+#    #+#             */
/*   Updated: 2023/09/15 18:14:01 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// ON EXECUTE LA BONNE FONCTION //
int	get_func(t_fork_opt *fork_utils)
{
	int	id;

	id = fork_utils->cmd_id;
	if (id == MK_CD_REMAKE)
		cd_remake(fork_utils->cmdopt);
	if (id == MK_ECHO_REMAKE)
		echo_remake(fork_utils->cmdopt);
	if (id == MK_UNSET_ALL_ENV_VAR)
		unset_all_env_var(fork_utils->cmdopt);
	if (id == MK_DISPLAY_ENV)
		display_env(fork_utils->str, fork_utils->cmdopt);
	if (id == MK_EXPORT_ALL_VAR)
		export_all_var(fork_utils->cmdopt);
	if (id == MK_PRINT_PWD)
		print_pwd();
	if (id == MK_DISPLAY_ENV)
		free_d_array(fork_utils->str);
	free_everything(fork_utils->cmdopt, true);
	return (g_error_code);
}

// ON FORK NOS BUILTINS //
void	fork_it(t_fork_opt *fork_utils)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("pid"), (void)1);
	if (pid == 0)
		exit(get_func(fork_utils));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		errno = WEXITSTATUS(status);
		update_err_code((int)errno);
	}
}

// ON IDENTIFIT LES FONCTIONS EN UTILISANT DES "MARKER" //
int	get_marker_value(t_fork_opt *fork_utils)
{
	t_cmd_and_opt	*cmdopt;

	cmdopt = fork_utils->cmdopt;
	if (cmp(cmdopt->command_name, "cd"))
		return (MK_CD_REMAKE);
	else if (cmp(cmdopt->command_name, "echo"))
		return (MK_ECHO_REMAKE);
	else if (cmp(cmdopt->command_name, "unset"))
		return (MK_UNSET_ALL_ENV_VAR);
	else if (verif_if_env_called(cmdopt) && !cmdopt->opt_ty_tb.tab[1])
		return (MK_DISPLAY_ENV);
	else if (cmp(cmdopt->command_name, "export"))
		return (MK_EXPORT_ALL_VAR);
	else if (cmp(cmdopt->command_name, "pwd"))
		return (MK_PRINT_PWD);
	else if (!ft_strchr(cmdopt->command_path, '/'))
		return (ft_printf("\033[31m%s\033[0m : command not found\n",
				cmdopt->command_name), free_cmdopt(cmdopt),
			update_err_code(127), -1);
	return (0);
}

// TROUVER ET EXECUTER LA FONCTION EN FORK //
int	find_command_pipex(t_cmd_and_opt *cmdopt)
{
	t_fork_opt	fork_utils;
	int			mk;

	init_fork_opt(&fork_utils);
	fork_utils.cmdopt = cmdopt;
	mk = get_marker_value(&fork_utils);
	if (mk != 0)
	{
		if (mk == 4)
			fork_utils.str = get_env();
		fork_utils.cmd_id = mk;
		fork_it(&fork_utils);
	}
	if (mk == 0)
	{
		if (!run_execve(cmdopt))
			return (0);
	}
	return (g_error_code);
}

// FONCTION PRINCIPALE DE PIPEX //
void	execute_pipex(char **lst_cmd)
{
	t_cmd_and_opt	cmdopt;
	int				idx;

	idx = 0;
	init_cmdopt(&cmdopt);
	while (lst_cmd[idx])
	{
		create_command(lst_cmd[idx], &cmdopt);
		find_command_pipex(&cmdopt);
		free_cmdopt(&cmdopt);
		ft_printf("\n");
		idx++ ;
	}
}
