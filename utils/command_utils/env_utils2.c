/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:20:34 by wolf              #+#    #+#             */
/*   Updated: 2023/07/06 11:49:34 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// VERIF ENV AND PATH
void	verif_env_and_path(t_cmd_and_opt *cmdopt)
{
	cmdopt->path_unset = 0;
	cmdopt->pwd_unset = 0;
	if (!get_env()[0])
		return (rebuild_env());
	if (ft_getenv("PATH"))
		cmdopt->path_unset = 1;
	if (ft_getenv("PWD"))
		cmdopt->pwd_unset = 1;
	return ;
}

// REBUILD ENV
void	rebuild_env(void)
{
	char	*pwd_print;
	char	*pwd;

	pwd_print = get_pwd();
	pwd = ft_join(ft_strdup("PWD="), pwd_print);
	export_var(pwd);
	export_var("SHLVL=1");
	export_var("_=/usr/bin/env");
	free(pwd);

	return ;
}