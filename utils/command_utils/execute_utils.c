/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:57:10 by wolf              #+#    #+#             */
/*   Updated: 2023/06/27 16:08:23 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-// 


//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-// 

void	run_execve(t_cmd_and_opt *cmdopt)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(cmdopt->command_path, cmdopt->opt_tab, NULL) == -1)
		{
			ft_printf("bash : \033[31m%s\033[0m : %s\n", cmdopt->command_path,
				strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(EXIT_FAILURE);
	}
}

char	*brut_name(char *command_np)
{
	char	**str_split;
	char	*brut_command_name;

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
	if (!cmdopt->command_name)
		return ;
	if (cmp(cmdopt->command_name, "echo"))
		return (echo_remake(cmdopt));
	if (cmp(cmdopt->command_name, "cd"))
		return (cd_remake(cmdopt));
	if (cmp(cmdopt->command_name, "unset"))
		return (unset_all_env_var(cmdopt));
	if (cmp(cmdopt->command_name, "env"))
		return (display_env());
	run_execve(cmdopt);
}
