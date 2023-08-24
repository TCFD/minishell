/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:56:59 by zbp15             #+#    #+#             */
/*   Updated: 2023/08/24 21:59:29 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_by_value(char *var_name, char *value)
{
	char	*tmp;

	tmp = ft_join(ft_strdup(var_name), ft_strdup(value));
	return (tmp);
}

void	write_env_oldpwd(char *oldpwd)
{
	update_env_oldpwd(oldpwd);
	export_var(get_env_oldpwd());
}

void	write_env_pwd(char *pwd)
{
	update_env_pwd(pwd);
	export_var(get_env_pwd());
}
