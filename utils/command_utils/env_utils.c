/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:33:51 by wolf              #+#    #+#             */
/*   Updated: 2023/08/18 18:39:58 by rciaze           ###   ########.fr       */
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
void	unset_env_var(char *variable, char **env)
{
	char	**env_;
	int		i;
	int		ij;

	env_ = env;
	i = 0;
	while (env_[i])
	{
		if (ft_strncmp(env_[i], variable, ft_strlen(variable)) == 0
			&& env_[i][ft_strlen(variable)] == '=')
		{
			ij = 1;
			while (env_[i + ij - 1])
			{
				env_[i + ij - 1] = env_[i + ij];
				ij++ ;
			}
			env_[i + ij] = NULL;
			return ((void)update_err_code(0), update_env(env_));
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
		unset_env_var(cmdopt->opt_ty_tb.tab[idx], get_env());
	ft_printf("Fin unset\n");
}

// DISPLAY ENV
void	display_env(char **env, t_cmd_and_opt *cmdopt)
{
	int		idx;

	if (!cmp(cmdopt->command_path, "/bin/env")
		&& !cmp(cmdopt->command_path, "/usr/bin/env"))
	{
		if (cmdopt->path_unset == 1)
		{
			if (!ft_getenv("PATH")
				|| !does_command_path_valid(ft_strdup("env")))
				return ((void)update_err_code((int)errno),
					(void)ft_printf("Minishell : env : No such file or directory\n"));
		}
	}
	idx = -1;
	while (env[++idx])
		ft_printf("%s\n", env[idx]);
}
