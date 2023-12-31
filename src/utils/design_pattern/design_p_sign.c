/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:19:39 by wolf              #+#    #+#             */
/*   Updated: 2023/09/23 00:07:12 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_sign_ctrl(int value)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	singleton2->sign_ctrl = value;
}

int	get_sign_ctrl(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	return (singleton2->sign_ctrl);
}

void	update_last_sign(int value)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	singleton2->last_sign = value;
}

int	get_last_sign(void)
{
	t_singleton2	*singleton2;

	singleton2 = get_singleton2_instance();
	return (singleton2->last_sign);
}
