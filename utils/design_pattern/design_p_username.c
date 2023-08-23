/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_username.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:58:54 by wolf              #+#    #+#             */
/*   Updated: 2023/08/23 15:43:41 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_singleton	*get_singleton_instance(void)
{
	static t_singleton	instance;

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
