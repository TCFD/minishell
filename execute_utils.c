/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:57:10 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 19:42:44 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (execve(cmdopt->command_path, cmdopt->option, NULL) == -1)
		{
			ft_printf("sh : \033[31m%s\033[0m : %s\n", cmdopt->command_path, strerror(errno));
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
	return (brut_command_name);
}

void	execute_command(t_cmd_and_opt *cmdopt)
{
	if (!cmdopt->command_name)
		return ;
	if (ft_strncmp(cmdopt->command_name, "echo", 4) == 0)
		//------fonction spéciale reproduce_echo(char *str)
		return ;
	if (ft_strncmp(cmdopt->command_name, "cd", 2) == 0)
		//------fonction spéciale reproduce_cd(char *path)
		return ;
	run_execve(cmdopt);
}
