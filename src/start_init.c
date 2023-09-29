/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:46:03 by wolf              #+#    #+#             */
/*   Updated: 2023/09/29 18:36:03 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_brut_cmd_result(char *cmd)
{
	t_cmd_and_opt	cmdopt;
	char			*result;

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);
	create_command(cmd, &cmdopt);
	free(cmdopt.opt_ty_tb.tab[0]);
	cmdopt.opt_ty_tb.tab[0] = ft_strdup(cmdopt.command_path);
	if (!cmdopt.opt_ty_tb.tab[0])
		return (free_cmdopt(&cmdopt), malloc_failure(), NULL);
	result = get_execve_return(&cmdopt);
	free_cmdopt(&cmdopt);
	return (result);
}

void	initialise_home_path(void)
{
	t_cmd_and_opt	cmdopt;
	char			*find_path;
	char			**split_it;
	char			*result;
	char			*cmd;

	init_cmdopt(&cmdopt);
	verif_env_and_path(&cmdopt);
	cmd = ft_join_strdup("/bin/getent passwd ", get_username());
	if (!cmd)
		return (malloc_failure());
	find_path = get_brut_cmd_result(cmd);
	if (!find_path)
		return (free(cmd), malloc_failure());
	free(cmd);
	split_it = ft_split(find_path, ':');
	if (!split_it)
		return (free(find_path), malloc_failure());
	result = ft_strdup(split_it[d_len(split_it) - 2]);
	if (!result)
		return (malloc_failure());
	free_d_array(split_it);
	free(find_path);
	update_home_path(ft_strdup(result));
	free(result);
}
