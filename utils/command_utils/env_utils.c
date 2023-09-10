/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:33:51 by wolf              #+#    #+#             */
/*   Updated: 2023/09/10 17:14:05 by wolf             ###   ########.fr       */
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
	errno = 0;
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
void	unset_env_var(char *variable)
{
	char	**env_;
	int		i;
	int		ij;

	env_ = get_env();
	i = 0;
	while (env_[i])
	{
		if (ft_strncmp(env_[i], variable, ft_strlen(variable)) == 0
			&& env_[i][ft_strlen(variable)] == '=')
		{
			ij = 1;
			while (env_[i + ij - 1])
			{
				if (ij == 1)
					free(env_[i + ij - 1]);
				env_[i + ij - 1] = env_[i + ij];
				ij++ ;
			}
			env_[i + ij - 1] = NULL;
			break ;
		}
		i++ ;
	}
	return ((void)update_err_code(0), update_env(env_));
}

// UNSET ALL ENV VAR
void	unset_all_env_var(t_cmd_and_opt *cmdopt)
{
	int	idx;

	idx = 0;
	ft_printf("Debut unset\n");
	while (cmdopt->opt_ty_tb.tab[++idx])
		unset_env_var(cmdopt->opt_ty_tb.tab[idx]);
	ft_printf("Fin unset\n");
}

// DISPLAY ENV
void	display_env(char **env, t_cmd_and_opt *cmdopt)
{
	int		idx;

	(void)(cmdopt);
	idx = -1;
	while (env[++idx])
		ft_printf("%s\n", env[idx]);
}
