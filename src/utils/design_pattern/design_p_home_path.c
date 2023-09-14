/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_home_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:24:14 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/14 16:23:20 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_home_path(char *new_value)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	if (singleton->home_path)
		free(singleton->home_path);
	singleton->home_path = new_value;
}

char	*get_home_path(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->home_path);
}
