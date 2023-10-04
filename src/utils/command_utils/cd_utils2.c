/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:56:59 by zbp15             #+#    #+#             */
/*   Updated: 2023/10/04 17:22:03 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*join_by_value(char *var_name, char *value)
{
	char	*tmp;

	tmp = ft_join_strdup(var_name, value);
	return (tmp);
}

void	write_env_oldpwd(char *oldpwd)
{
	update_env_oldpwd(oldpwd);
	export_var(get_env_oldpwd(), true, get_env());
}

void	write_env_pwd(char *pwd)
{
	update_env_pwd(pwd);
	export_var(get_env_pwd(), true, get_env());
}
