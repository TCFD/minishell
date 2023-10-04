/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:46:03 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 16:57:10 by rciaze           ###   ########.fr       */
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
	cmdopt.opt_ty_tb.tab[0] = ft_strdup(cmdopt.command_path);
	result = get_execve_return(&cmdopt);
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
	find_path = get_brut_cmd_result(cmd);
	if (!find_path)
		return (malloc_failure());
	split_it = ft_split(find_path, ':');
	result = ft_strdup(split_it[d_len(split_it) - 2]);
	if (!result)
		return (malloc_failure());
	update_home_path(ft_strdup(result));
}
