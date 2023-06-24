/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:33:51 by wolf              #+#    #+#             */
/*   Updated: 2023/06/24 12:23:44 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_env_var(char *variable)
{
	char	**env_;
	int		i;
	int		ij;

	ft_printf("IN, variable : %s\n", variable);
	env_ = environ;
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
}

void	unset_all_env_var(t_cmd_and_opt *cmdopt)
{
	int	idx;

	idx = 0;
	while (cmdopt->opt_tab[++idx])
		unset_env_var(cmdopt->opt_tab[idx]);
}

void	display_env(void)
{
	char	**env_;
	int	idx;

	if (!getenv("PATH"))
		return ((void)ft_printf("bash : env : No such file or directory\n")); // Rajouter l'erreur errno
	env_ = environ;
	idx = -1;
	while (env_[++idx])
		ft_printf("%s\n", env_[idx]);
}
