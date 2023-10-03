/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:24:14 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/03 15:34:45 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd(char *new_value)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	if (singleton->pwd)
		free(singleton->pwd);
	singleton->pwd = new_value;
}

char	*get_pwd_path(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->pwd);
}
