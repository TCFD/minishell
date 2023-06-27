/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:58:54 by wolf              #+#    #+#             */
/*   Updated: 2023/06/27 16:36:19 by rciaze           ###   ########.fr       */
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
	if (singleton->last_value != NULL)
		free(singleton->last_value);
	singleton->last_value = ft_strdup(newValue);
}

const char	*get_username(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->last_value);
}

void	free_last_value(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	if (singleton->last_value != NULL)
	{
		free(singleton->last_value);
		singleton->last_value = NULL;
	}
}
