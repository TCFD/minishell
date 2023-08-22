/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:44:30 by tboldrin          #+#    #+#             */
/*   Updated: 2023/08/22 09:43:22 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_code;

void	update_err_code(int code_err)
{
	if (code_err == 13)
		error_code = 126;
	else if (code_err == 5 || code_err == 9
		|| code_err == 12 || code_err == 17
		|| code_err == 25)
		error_code = 127;
	else if (code_err == 32)
		error_code = 141;
	else if (code_err == 0)
		error_code = 0;
	else
		error_code = code_err;
}
