/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_username.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:58:54 by wolf              #+#    #+#             */
/*   Updated: 2023/09/14 16:23:20 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_singleton	*get_singleton_instance(void)
{
	static t_singleton	instance;

	return (&instance);
}

t_singleton2	*get_singleton2_instance(void)
{
	static t_singleton2	instance;

	return (&instance);
}

void	update_username(const char *newValue)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	if (singleton->username != NULL)
		free(singleton->username);
	singleton->username = (char *)newValue;
}

char	*get_username(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->username);
}

void	free_last_value(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	if (singleton->username != NULL)
	{
		free(singleton->username);
		singleton->username = NULL;
	}
}
