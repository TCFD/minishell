/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:20:34 by wolf              #+#    #+#             */
/*   Updated: 2023/06/30 15:30:11 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* void	realloc_environ(int line, char *variable)
{
	int	idx;

	idx = 0;
	return ;
} */

/* void	export_env_var(char *variable)
{
	char	**env_;
	int		idx;
	
	idx = -1;
	env_ = environ;
	if (getenv(variable))
	{
		while (environ[++idx])
		{
			if (ft_strncmp(env_[i], variable, ft_strlen(variable)) == 0
				&& env_[i][ft_strlen(variable)] == '=')
				break;
		}
		
	}
} */

void	verif_env_and_path(t_cmd_and_opt *cmdopt)
{
	if (!get_env())
		return (rebuild_env());
	if (!ft_getenv("PATH"))
	{
		cmdopt->path_unset = 1;
		return ;
	}
	//if (!getenv("SHLVL"))
	//	export_var("SHLVL=1");
	if (!ft_getenv("SHLVL"))
		ft_printf("SHLVL will be set a 1\n");
	cmdopt->path_unset = 0;
	return ;
}

void	rebuild_env(void)
{
	//export_var(get_execve_return(cmdopt)) // PWD
	//export_var("SHLVL=1");				// SHLVL
	//_=
	//
	
	ft_printf("--> env Rebuilding\n");

	return ;
}