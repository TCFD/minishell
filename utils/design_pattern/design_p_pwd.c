/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:24:14 by tboldrin          #+#    #+#             */
/*   Updated: 2023/08/11 22:55:24 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_singleton	*get_pwd_instance(void)
{
	static t_singleton	instance;
	return (&instance);
}

void	update_pwd(char *new_value)
{
	t_singleton	*singleton;

	singleton = get_pwd_instance();
	if (singleton->pwd)
		free(singleton->pwd);
	singleton->pwd = new_value;
}

char	*get_pwd_path(void)
{
	t_singleton	*singleton;

	singleton = get_pwd_instance();
	return (singleton->pwd);
}
