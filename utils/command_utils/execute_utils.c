/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:57:10 by wolf              #+#    #+#             */
/*   Updated: 2023/08/09 13:42:03 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_execve(t_cmd_and_opt *cmdopt)
{
	pid_t		pid;
	int			status;

	errno = 0;
	pid = fork();
	if (pid == -1)
		return ((void)update_err_code((int)errno),
			perror("fork"), exit(EXIT_FAILURE));
	else if (pid == 0)
	{
		if (execve(cmdopt->command_path, cmdopt->opt_ty_tb.tab, get_env())
			== -1)
		{
			ft_printf("bash : \033[31m%s\033[0m : %s\n", cmdopt->command_path,
				strerror(errno));
			return (free_cmdopt(cmdopt), exit(errno));
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
	}
	update_err_code((int)errno);
}

char	*brut_name(char *command_np)
{
	char	**str_split;
	char	*brut_command_name;

	if (!ft_strchr(command_np, '/'))
		return (command_np);
	str_split = ft_split(command_np, '/');
	brut_command_name = ft_cpy(str_split[d_len(str_split) - 1], 0);
	free_d_array(str_split);
	free(command_np);
	return (brut_command_name);
}

int	cmp(char *cmd_name, char *cmd_name_2)
{
	if (ft_strncmp(cmd_name, cmd_name_2, ft_strlen(cmd_name_2)) == 0
		&& ft_strlen(cmd_name) == ft_strlen(cmd_name_2))
		return (1);
	return (0);
}

void	execute_command(t_cmd_and_opt *cmdopt)
{
	t_redirections	redirections;
	bool			redir_out_bool;
	bool			redir_in_bool;

	if (!cmdopt->command_name)
		return ;
	if (search_in_redirections(cmdopt, &redirections, &redir_in_bool) == 0)
		return ;
	if (search_out_redirections(cmdopt, &redirections, &redir_out_bool) == 0)
		return ;
	free(cmdopt->opt_ty_tb.tab[0]);
	cmdopt->opt_ty_tb.tab[0] = ft_strdup(cmdopt->command_path);
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
	else if (!cmdopt->command_path[0])
		return (ft_printf("bash : \033[31m%s\033[0m : command not found\n",
				cmdopt->command_name), free_cmdopt(cmdopt), update_err_code(127));
	else
		run_execve(cmdopt);
	if (redir_in_bool)
		restore_stdin(&redirections);
	if (redir_out_bool)
		restore_stdout(redirections.stdout_save, redirections.file_out_fd);
}
