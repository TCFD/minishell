/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:20:34 by wolf              #+#    #+#             */
/*   Updated: 2023/07/03 19:04:00 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// VERIF ENV AND PATH
void	verif_env_and_path(t_cmd_and_opt *cmdopt)
{
	cmdopt->path_unset = 0;
	if (!get_env()[0])
		return (rebuild_env(cmdopt));
	if (ft_getenv("PATH"))
	{
		cmdopt->path_unset = 1;
		return ;
	}
	return ;
}

// REBUILD ENV
void	rebuild_env(t_cmd_and_opt *cmdopt)
{
	char	*pwd;

	create_command("/bin/pwd", cmdopt);
	pwd = ft_join(ft_strdup("PWD="), ft_strdup(get_execve_return(cmdopt)));
	export_var(pwd);
	export_var("SHLVL=1");
	export_var("_=/usr/bin/env");
	free(pwd);

	return ;
}