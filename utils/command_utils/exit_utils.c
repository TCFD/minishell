/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:41:50 by tboldrin          #+#    #+#             */
/*   Updated: 2023/08/20 18:22:53 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_err_code_exit(char *origin_code, int code_err)
{
	
	char	*str;
	str = ft_itoa(code_err);
	free_env_singleton();
	if (!str)
		return (free(str), exit(EXIT_FAILURE));
	if (ft_strncmp(str, origin_code, ft_len(origin_code)) != 0)
		return ((void)printf("bash: exit: %s : argument numérique nécessaire\n", origin_code),
		exit(2));
	code_err = code_err % 256;
	errno = code_err;
	update_err_code(code_err);
	exit(code_err);
}

void	ft_exit(char *code_err)
{
	if (ft_len(code_err) > 0 && code_err[0] != '\0')
		(void)update_err_code_exit(code_err, ft_atoi(code_err));
	free(code_err);
}
