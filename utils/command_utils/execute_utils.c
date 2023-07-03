/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:57:10 by wolf              #+#    #+#             */
/*   Updated: 2023/07/03 14:37:17 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_execve(t_cmd_and_opt *cmdopt)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), exit(EXIT_FAILURE));
	else if (pid == 0)
	{
		if (execve(cmdopt->command_path, cmdopt->opt_and_type_tab.tab, get_env()) == -1)
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
	long int	position;
	int			stdout_save;
	int			filefd;

	if (!cmdopt->command_name)
		return ;
	search_redirections(cmdopt, &stdout_save, &filefd, &position);
	if (cmp(cmdopt->command_name, "cd"))
		cd_remake(cmdopt);
	else if (cmp(cmdopt->command_name, "unset"))
		unset_all_env_var(cmdopt);
	else if (cmp(cmdopt->command_name, "env") && !cmdopt->opt_and_type_tab.tab[1])
		display_env(get_env(), cmdopt);
	else if (cmp(cmdopt->command_name, "export"))
		export_all_var(cmdopt);
	else
		run_execve(cmdopt);
	restore_fd(position, stdout_save, filefd);
}
