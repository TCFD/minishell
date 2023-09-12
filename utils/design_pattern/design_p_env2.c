/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_env2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:25:53 by wolf              #+#    #+#             */
/*   Updated: 2023/09/12 16:28:04 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_fix_env_detection(void)
{
	t_singleton2	*singleton;

	singleton = get_singleton2_instance();
	return (singleton->fix_env_i);
}
