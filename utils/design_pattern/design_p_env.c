/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:55:00 by wolf              #+#    #+#             */
/*   Updated: 2023/08/20 17:04:30 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_singleton	*get_env_instance(void)
{
	static t_singleton	instance;

	return (&instance);
}

void	update_env(char **new_value)
{
	t_singleton	*singleton;

	singleton = get_env_instance();
	if (singleton && singleton->env != NULL)
	{
		singleton->env = new_value;
		return ;
	}
	singleton->env = new_value;
}

char	**get_env(void)
{
	t_singleton	*singleton;

	singleton = get_env_instance();
	return (singleton->env);
}

void	free_env_singleton(void)
{
	t_singleton	*singleton;

	singleton = get_env_instance();
	if (singleton->env != NULL)
	{
		free_d_array(singleton->env);
		singleton->env = NULL;
	}
}
