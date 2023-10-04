/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:23:45 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 17:20:54 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_env_pwd(char *new_value)
{
	static int	count;
	t_singleton	*singleton;

	count++ ;
	singleton = get_singleton_instance();
	singleton->env_pwd = new_value;
}

void	update_env_oldpwd(char *new_value)
{
	static int	count;
	t_singleton	*singleton;

	count++ ;
	singleton = get_singleton_instance();
	singleton->env_oldpwd = new_value;
}

char	*get_env_pwd(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->env_pwd);
}

char	*get_env_oldpwd(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->env_oldpwd);
}
