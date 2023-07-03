/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:01:53 by wolf              #+#    #+#             */
/*   Updated: 2023/07/03 19:42:43 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// EXPORT NAME UNVALID
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

// EXPORT VAR
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

// EXPORT ALL VAR
void	export_all_var(t_cmd_and_opt *cmdopt)
{
	char	**env;
	int		idx;
	int		sub_idx;

	idx = 0;
	sub_idx = -1;
	if (!cmdopt->opt_and_type_tab.tab[1])
	{
		env = get_env();
		while (env[++sub_idx])
			ft_printf("%sdeclare -x %s%s\n", NC, env[sub_idx], NC);
		return ;
	}
	while (cmdopt->opt_and_type_tab.tab[++idx])
		export_var(cmdopt->opt_and_type_tab.tab[idx]);
	verif_env_and_path(cmdopt);
}
