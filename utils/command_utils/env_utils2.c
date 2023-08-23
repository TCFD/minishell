/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:20:34 by wolf              #+#    #+#             */
/*   Updated: 2023/08/23 10:35:20 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// VERIF ENV AND PATH
void	verif_env_and_path(t_cmd_and_opt *cmdopt)
{
	cmdopt->path_unset = 0;
	if (!get_env()[0])
		return (rebuild_env());
	if (ft_getenv("PATH"))
	{
		cmdopt->path_unset = 1;
		return ;
	}
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
	//free(pwd);
	return ;
}

char	*get_env_var(char *var_name)
{
	char	**env;
	char	**split_one;
	char	*final;
	int		idx;

	env = get_env();
	idx = 0;
	while (env[idx])
	{
		if (ft_strncmp(var_name, env[idx], ft_strlen(var_name)) == 0)
		{
			split_one = ft_split(env[idx], '=');
			printf("split_one : %s\n", split_one[1]);
			final = ft_strdup(split_one[1]);
			return (free_d_array(split_one), final);
		}
		idx++ ;
	}
	return (NULL);
}
