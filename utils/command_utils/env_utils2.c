/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:20:34 by wolf              #+#    #+#             */
/*   Updated: 2023/06/30 18:19:51 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (find_first_occurence(var, '$') == (int)ft_strlen(var) - 1)
		return (1);
	return (0);
}

// TROP DE FONCTIONS À BOUGER DANS UN AUTRE DOSSIER
/* char	*var_transform(char *var)
{
	char	*new_var;
	int		idx_of;

	idx_of = find_first_occurence(var, '\\');
	
}
*/

void	export_var(char *var)
{
	char	**split_name;
	char	**env;
	int		idx_var;
	
	if (export_name_unvalid(var))
		return ((void)ft_printf("bash : export: "), 
			(void)ft_printf("« %s » : identifiant non valable\n", var));
	if (var[0] == '=')
		return (
		(void)ft_printf("bash : export: « = » : identifiant non valable\n"));
	if (!ft_strchr(var, '='))
		return ;
	split_name = ft_split(var, '=');
	idx_var = ft_getenv_int(split_name[0]);
	env = get_env();
	if (idx_var != -1)
		env[idx_var] = var;
	else
		env = double_a_realloc(env, var);
	free_d_array(split_name);
	update_env(env);
}

void	export_all_var(t_cmd_and_opt *cmdopt)
{
	char	**env;
	int		idx;
	int		sub_idx;

	idx = 0;
	sub_idx = -1;
	if (!cmdopt->opt_tab[1])
	{
		env = get_env();
		while (env[++sub_idx])
			ft_printf("%sdeclare -x %s%s\n", NC, env[sub_idx], NC);
		return ;
	}
	while (cmdopt->opt_tab[++idx])
		export_var(cmdopt->opt_tab[idx]);
}

// ENV

void	verif_env_and_path(t_cmd_and_opt *cmdopt)
{
	cmdopt->path_unset = 0;
	if (!get_env()[0])
		return (rebuild_env(cmdopt));
	if (!ft_getenv("PATH"))
	{
		cmdopt->path_unset = 1;
		return ;
	}
	return ;
}

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