/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:58:54 by wolf              #+#    #+#             */
/*   Updated: 2023/06/24 15:49:13 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

Singleton	*get_singleton_instance(void)
{
	static Singleton	instance;
	return (&instance);
}

void	update_username(const char *newValue)
{
	Singleton	*singleton;
	
	singleton = get_singleton_instance();
	if (singleton->lastValue != NULL)
		free(singleton->lastValue);
	singleton->lastValue = ft_strdup(newValue);
}

const char	*get_username(void)
{
	Singleton *singleton = get_singleton_instance();
	return (singleton->lastValue);
}

void	free_last_value(void)
{
	Singleton	*singleton;
	
	singleton = get_singleton_instance();
	if (singleton->lastValue != NULL)
	{
		free(singleton->lastValue);
		singleton->lastValue = NULL;
	}
}
