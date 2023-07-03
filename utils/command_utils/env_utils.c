/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:33:51 by wolf              #+#    #+#             */
/*   Updated: 2023/07/03 15:27:35 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// FT GETENV
char	*ft_getenv(char *var_name)
{
	char	**env;
	int		idx;

	idx = 0;
	env = get_env();
	while (env[idx])
	{
		if (ft_strncmp(var_name, env[idx], ft_strlen(var_name)) == 0
			&& env[idx][ft_strlen(var_name)] == '=')
			return (env[idx] + ft_strlen(var_name) + 1);
		idx++ ;
	}
	return (NULL);
}

// FT GETENV INT
int	ft_getenv_int(char *var_name)
{
	char	**env;
	int		idx;

	idx = 0;
	env = get_env();
	while (env[idx])
	{
		if (ft_strncmp(var_name, env[idx], ft_strlen(var_name)) == 0
			&& env[idx][ft_strlen(var_name)] == '=')
			return (idx);
		idx++ ;
	}
	return (-1);
}

// UNSET ENV VAR
void	unset_env_var(char *variable, char **env)
{
	char	**env_;
	int		i;
	int		ij;

	ft_printf("IN, variable : %s\n", variable);
	env_ = env;
	i = 0;
	while (env_[i])
	{
		if (ft_strncmp(env_[i], variable, ft_strlen(variable)) == 0
			&& env_[i][ft_strlen(variable)] == '=')
		{
			ij = 1;
			while (env_[i + ij])
			{
				env_[i + ij - 1] = env_[i + ij];
				ij++ ;
			}
			env_[i + ij] = NULL;
			return (update_env(env_));
		}
		i++ ;
	}
	update_env(env_);
}

// UNSET ALL ENV VAR
void	unset_all_env_var(t_cmd_and_opt *cmdopt)
{
	int	idx;

	idx = 0;
	while (cmdopt->opt_and_type_tab.tab[++idx])
		unset_env_var(cmdopt->opt_and_type_tab.tab[idx], get_env());
}

// DISPLAY ENV
void	display_env(char **env, t_cmd_and_opt *cmdopt)
{
	int		idx;

	if (cmdopt->path_unset == 1)
	{
		if (!ft_getenv("PATH") || !does_command_path_valid(ft_strdup("env")))
			return ((void)ft_printf("bash : env : No such file or directory\n")); // Rajouter l'erreur errno
	}
	idx = -1;
	while (env[++idx])
		ft_printf("%s\n", env[idx]);
}
