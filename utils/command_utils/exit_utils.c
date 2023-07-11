/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:41:50 by tboldrin          #+#    #+#             */
/*   Updated: 2023/07/05 12:52:29 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_err_code_exit(int code_err)
{
	code_err = code_err % 256;
	errno = code_err;
	update_err_code(code_err);
	exit(code_err);
}

void	ft_exit(char *code_err)
{
	if (code_err[0] != '\0')
		update_err_code_exit(ft_atoi(code_err));
}