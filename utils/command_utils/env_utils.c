/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:33:51 by wolf              #+#    #+#             */
/*   Updated: 2023/06/30 15:36:38 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			return ;
		}
		i++ ;
	}
	update_env(env_);
}

void	unset_all_env_var(t_cmd_and_opt *cmdopt)
{
	int	idx;

	idx = 0;
	while (cmdopt->opt_tab[++idx])
		unset_env_var(cmdopt->opt_tab[idx], get_env());
}

void	display_env(char **env)
{
	int	idx;

	if (!ft_getenv("PATH"))
		return ((void)ft_printf("bash : env : No such file or directory\n")); // Rajouter l'erreur errno
	idx = -1;
	while (env[++idx])
		ft_printf("%s\n", env[idx]);
}
