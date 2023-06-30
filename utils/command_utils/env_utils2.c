/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:20:34 by wolf              #+#    #+#             */
/*   Updated: 2023/06/30 16:08:25 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* void	realloc_environ(int line, char *variable)
{
	int	idx;

	idx = 0;
	return ;
} */


int	export_name_unvalid(char *var)
{
	if (ft_strchr(var, '\''))
		return (1);
	if (ft_strchr(var, '@'))
		return (1);
	if (ft_strchr(var, '.'))
		return (1);
	if (ft_strchr(var, '-'))
		return (1);
	if (ft_strchr(var, ' '))
		return (1);
	return (0);
}


void	export_var(char *var)
{
	if (export_name_unvalid(var))
		return ((void)ft_printf("bash : export: "), 
			(void)ft_printf("« %s » : identifiant non valable\n", var));
}

void	export_all_var(t_cmd_and_opt *cmdopt)
{
	char	**env;
	int		idx;
	int		sub_idx;

	idx = 0;
	sub_idx = -1;
	ft_printf("cmdopt opt_tab [idx] : %s\n", cmdopt->opt_tab[idx + 1]);
	if (!cmdopt->opt_tab[1])
	{
		env = get_env();
		while (env[++sub_idx])
			ft_printf("%sdeclare -x %s%s\n", NC, env[sub_idx], NC);
	}
	while (cmdopt->opt_tab[++idx])
		export_var(cmdopt->opt_tab[idx]);
}

// ENV

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