/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   export_utils.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tboldrin <tboldrin@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/07/03 19:01:53 by wolf			  #+#	#+#			 */
/*   Updated: 2023/10/04 18:19:36 by tboldrin		 ###   ########.fr	   */
/*																			*/
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

void	sort(char **argv)
{
	int		i;
	char	*temp;
	int		must_continue;

	must_continue = 1;
	while (must_continue)
	{
		must_continue = 0;
		i = 1;
		while (argv[i + 1])
		{
			if (ft_strncmp(argv[i], argv[i + 1],
					ft_len(argv[i]) + ft_len(argv[i + 1])) > 0)
			{
				temp = argv[i];
				argv[i] = argv[i + 1];
				argv[i + 1] = temp;
				must_continue = 1;
			}
			i++;
		}
	}
}

void	sort_export(char **env)
{
	int		sub_idx;

	sort(env);
	sub_idx = -1;
	while (env[++sub_idx])
		ft_printf(STDOUT_FILENO, "%sdeclare -x %s%s\n", NC, env[sub_idx], NC);
}

// EXPORT ALL VAR
void	export_all_var(t_cmd_and_opt *cmdopt)
{
	int		idx;

	idx = 0;
	if (!cmdopt->opt_ty_tb.tab[1])
	{
		sort_export(ft_d_strdup(get_env()));
		return ((void)update_err_code(0));
	}
	while (cmdopt->opt_ty_tb.tab[++idx])
		export_var(cmdopt->opt_ty_tb.tab[idx], true, get_env());
	verif_env_and_path(cmdopt);
}
