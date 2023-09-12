/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:55:00 by wolf              #+#    #+#             */
/*   Updated: 2023/09/12 16:26:46 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_env(char **new_value)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	if (singleton && singleton->env != NULL)
	{
		singleton->env = new_value;
		return ;
	}
	singleton->env = new_value;
}

void	update_env_detection(int new_value)
{
	t_singleton2	*singleton;

	singleton = get_singleton2_instance();
	singleton->env_i = new_value;
	if (new_value == 1)
		singleton->fix_env_i = 1;
}

int	get_env_detection(void)
{
	t_singleton2	*singleton;

	singleton = get_singleton2_instance();
	return (singleton->env_i);
}

char	**get_env(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->env);
}

void	free_env_singleton(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	if (singleton->env != NULL)
	{
		free_d_array(singleton->env);
		singleton->env = NULL;
	}
}
