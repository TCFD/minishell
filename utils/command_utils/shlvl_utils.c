/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:54:52 by wolf              #+#    #+#             */
/*   Updated: 2023/06/30 15:30:30 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shlvl_plus_one(void)
{
	char	**split_to_int;
	char	*join_it;
	char	*shlvl;
	int		value;

	shlvl = ft_getenv("SHLVL");
	if (!shlvl)
		return ;
	split_to_int = ft_split(shlvl, '=');
	value = ft_atoi(split_to_int[d_len(split_to_int) - 1]) + 1;
	join_it = ft_join(ft_strdup("SHLVL="), ft_itoa(value));
	ft_printf("join_it_value : %s\n", join_it);
	//export_var(join_it);
	free_d_array(split_to_int);
	free(join_it);
}

void	shlvl_minus_one(void)
{
	char	**split_to_int;
	char	*join_it;
	char	*shlvl;
	int		value;

	shlvl = ft_getenv("SHLVL");
	if (!shlvl)
		return ;
	split_to_int = ft_split(shlvl, '=');
	value = ft_atoi(split_to_int[d_len(split_to_int) - 1]) - 1;
	join_it = ft_join(ft_strdup("SHLVL="), ft_itoa(value));
	ft_printf("join_it_value : %s\n", join_it);
	//export_var(join_it);
	free_d_array(split_to_int);
	free(join_it);
}