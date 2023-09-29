/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:46:03 by wolf              #+#    #+#             */
/*   Updated: 2023/09/28 22:12:36 by wolf             ###   ########.fr       */
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
		return (free_cmdopt(&cmdopt), NULL);
	result = get_execve_return(&cmdopt);
	if (!result)
		return (free_cmdopt(&cmdopt), malloc_fail(), NULL);
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
		return(free_cmdopt(&cmdopt), ft_exit(EXIT_FAILURE, false));
	find_path = get_brut_cmd_result(cmd);
	if (!find_path)
		return (free_cmdopt(&cmdopt), malloc_fail());
	split_it = ft_split(find_path, ':');
	if (!split_it)
		return (free(cmd), free_cmdopt(&cmdopt), malloc_fail());
	result = ft_strdup(split_it[d_len(split_it) - 2]);
	if (!result)
		return (
			free_d_array(split_it), free_cmdopt(&cmdopt), free(cmd), malloc_fail());
	free(cmd);
	free_d_array(split_it);
	free(find_path);
	update_home_path(ft_strdup(result));
	free(result);
}
