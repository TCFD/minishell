/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:01:53 by wolf              #+#    #+#             */
/*   Updated: 2023/08/22 13:00:05 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// EXPORT NAME UNVALID
int	export_name_unvalid(char *var)
{
	int	i;

	i = -1;
	while(var[++i] != '=' && var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
	}
	return (0);
}

// EXPORT VAR
void	export_var(char *var)
{
	char	**split_name;
	char	**env;
	char	**new_env;
//	char	*savetamere;
	int		idx_var;

	if (export_name_unvalid(var))
		return ((void)update_err_code(1), (void)ft_printf("Minishell : export: "),
			(void)ft_printf("`%s': identifiant non valable\n", var));
	if (!ft_strchr(var, '='))
		return ;
	split_name = ft_split(var, '=');
//	savetamere = ft_strdup(split_name[1]);
	idx_var = ft_getenv_int(split_name[0]);
	env = get_env();
	if (idx_var != -1)
	{
		free(env[idx_var]); // Pose prb
		env[idx_var] = var;
		new_env = env;
	}
	else
		new_env = double_a_realloc(env, var);
//	split_name[1] = savetamere;
	free_d_array(split_name);
	update_err_code(0);
	update_env(new_env);
}

// EXPORT ALL VAR
void	export_all_var(t_cmd_and_opt *cmdopt)
{
	char	**env;
	int		idx;
	int		sub_idx;

	idx = 0;
	sub_idx = -1;
	if (!cmdopt->opt_ty_tb.tab[1])
	{
		env = get_env();
		while (env[++sub_idx])
			ft_printf("%sdeclare -x %s%s\n", NC, env[sub_idx], NC);
		return ((void)update_err_code(0));
	}
	while (cmdopt->opt_ty_tb.tab[++idx])
		export_var(cmdopt->opt_ty_tb.tab[idx]);
	verif_env_and_path(cmdopt);
}
