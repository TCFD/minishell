/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:54:52 by wolf              #+#    #+#             */
/*   Updated: 2023/08/20 17:01:30 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shlvl_plus_one(char **join_it)
{
	char	*shlvl;
	int		value;

	shlvl = ft_getenv("SHLVL");
	if (!shlvl)
		return ;
	value = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(value);
	if (!shlvl)
		return ;
	*join_it = ft_join(ft_strdup("SHLVL="), shlvl);
	export_var(*join_it);
}

void	shlvl_minus_one(void)
{
	char	*join_it;
	char	*shlvl;
	int		value;

	shlvl = ft_getenv("SHLVL");
	if (!shlvl)
		return ;
	value = ft_atoi(shlvl) - 1;
	shlvl = ft_itoa(value);
	if (!shlvl)
		return ;
	join_it = ft_join(ft_strdup("SHLVL="), shlvl);
	export_var(join_it);
}
