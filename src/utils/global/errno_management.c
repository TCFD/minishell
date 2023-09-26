/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:44:30 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/26 17:35:30 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	g_error_code;

void	update_err_code(int code_err)
{
	if (code_err == 13)
		g_error_code = 126;
	else if (code_err == 22)
		g_error_code = 1;
	else if (code_err == 5 || code_err == 9
		|| code_err == 12 || code_err == 17
		|| code_err == 25)
		g_error_code = 127;
	else if (code_err == 32)
		g_error_code = 141;
	else if (code_err == 0)
		g_error_code = 0;
	else
		g_error_code = code_err;
}
