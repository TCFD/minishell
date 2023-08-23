/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:41:50 by tboldrin          #+#    #+#             */
/*   Updated: 2023/08/23 12:26:08 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_message(int code)
{
	bf_prd("\n➜ Outstanding \033[5m🙏\033[0m\033[32m ?\n\n", 75000000, GREEN);
	exit(code);
}

void	update_err_code_exit(char *origin_code, int code_err)
{
	
	char	*str;
	str = ft_itoa(code_err);
	free_env_singleton();
	if (!str)
		return (free(str), free(origin_code), exit_message(EXIT_FAILURE));
	if (ft_strncmp(str, origin_code, ft_len(origin_code)) != 0)
		return ((void)ft_printf("Minishell: exit: %s : argument numérique nécessaire\n", origin_code),
		free(str), free(origin_code), exit_message(2));
	code_err = code_err % 256;
	errno = code_err;
	update_err_code(code_err);
	free(origin_code);
	free(str);
	exit_message(code_err);
}

void	ft_exit(char *code_err)
{
	if (ft_len(code_err) > 0 && code_err[0] != '\0')
		update_err_code_exit(code_err, ft_atoi(code_err));
	free(code_err);
}
