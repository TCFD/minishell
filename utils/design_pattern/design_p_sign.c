/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:19:39 by wolf              #+#    #+#             */
/*   Updated: 2023/08/15 22:32:55 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_sign_ctrl(int value)
{
	t_singleton	*singleton;

	singleton = get_env_instance();
	singleton->sign_ctrl = value;
}

int	get_sign_ctrl(void)
{
	t_singleton	*singleton;

	singleton = get_env_instance();
	return (singleton->sign_ctrl);
}
