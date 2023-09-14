/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:54:52 by wolf              #+#    #+#             */
/*   Updated: 2023/09/14 16:23:20 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env_var_plus_one(char *env_var)
{
	char	*join_it;
	char	*shlvl;
	int		value;

	shlvl = ft_getenv(env_var);
	if (!shlvl)
		return ;
	value = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(value);
	if (!shlvl)
		return ;
	join_it = ft_join(ft_join(ft_strdup(env_var), ft_strdup("=")), shlvl);
	export_var(join_it);
	free(join_it);
}

void	env_var_minus_one(char *env_var)
{
	char	*join_it;
	char	*shlvl;
	int		value;

	shlvl = ft_getenv(env_var);
	if (!shlvl)
		return ;
	value = ft_atoi(shlvl) - 1;
	shlvl = ft_itoa(value);
	if (!shlvl)
		return ;
	join_it = ft_join(ft_join(ft_strdup(env_var), ft_strdup("=")), shlvl);
	export_var(join_it);
	free(join_it);
}
