/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:01:53 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 17:15:40 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// EXPORT NAME UNVALID
int	export_name_unvalid(char *var)
{
	int	i;

	if (ft_atoi(var) == 0 && var[0] == '0')
		return (1);
	if (ft_atoi(var) != 0)
		return (1);
	if (var[0] == '=')
		return (1);
	i = -1;
	while (var[++i] != '=' && var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
	}
	return (0);
}

// EXPORT VAR
void	export_var(char *var, bool update_g, char **env)
{
	char	**split_name;
	int		idx_var;

	if (export_name_unvalid(var))
		return ((void)update_err_code(1),
			(void)ft_printf(STDERR_FILENO, "Minishell : export: `%s':"
				" identifiant non valable\n", var));
	if (!ft_strchr(var, '='))
		return ;
	split_name = ft_split(var, '=');
	idx_var = ft_getenv_int(split_name[0]);
	if (idx_var != -1)
	{
		env[idx_var] = ft_strdup(var);
		update_env(env);
	}
	else
		update_env(double_a_realloc(env, ft_strdup(var)));
	if (update_g == true)
		update_err_code(0);
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
			ft_printf(STDOUT_FILENO, "%sdeclare -x %s%s\n", NC,
				env[sub_idx], NC);
		return ((void)update_err_code(0));
	}
	while (cmdopt->opt_ty_tb.tab[++idx])
		export_var(cmdopt->opt_ty_tb.tab[idx], true, get_env());
	verif_env_and_path(cmdopt);
}
