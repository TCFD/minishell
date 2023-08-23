/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:23:45 by wolf              #+#    #+#             */
/*   Updated: 2023/08/23 10:32:13 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_env_pwd(char *new_value)
{
	static int	count;
	t_singleton	*singleton;

	count++ ;
	singleton = get_env_instance();
	if (count > 1 && singleton->env_pwd != NULL)
		free(singleton->env_pwd);
	singleton->env_pwd = new_value;
}

void	update_env_oldpwd(char *new_value)
{
	static int	count;
	t_singleton	*singleton;

	count++ ;
	singleton = get_env_instance();
	if (count > 1 && singleton->env_oldpwd != NULL)
		free(singleton->env_oldpwd);
	singleton->env_oldpwd = new_value;
}

char	*get_env_pwd(void)
{
	t_singleton	*singleton;

	singleton = get_env_instance();
	return (singleton->env_pwd);
}

char	*get_env_oldpwd(void)
{
	t_singleton	*singleton;

	singleton = get_env_instance();
	return (singleton->env_oldpwd);
}