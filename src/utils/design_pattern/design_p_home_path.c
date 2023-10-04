/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_home_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:24:14 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 17:21:11 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_home_path(char *new_value)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	singleton->home_path = new_value;
}

char	*get_home_path(void)
{
	t_singleton	*singleton;

	singleton = get_singleton_instance();
	return (singleton->home_path);
}
