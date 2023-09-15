/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_sign2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:46 by wolf              #+#    #+#             */
/*   Updated: 2023/09/15 12:48:01 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_last_sign_ctrl(int value)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	singleton2->last_sign_ctrl = value;
}

int	get_last_sign_ctrl(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	return (singleton2->last_sign_ctrl);
}
