/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:41:50 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/22 19:34:21 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit(int code, bool msg)
{
	if (msg)
	{
		ft_printf("exit\n");
		//one_time_animation_end();
	}
	update_pwd(NULL);
	free(get_env_pwd());
	free(get_env_oldpwd());
	free(get_home_path());
	free(get_username());
	free_env_singleton();
	exit(code);
}

void	update_err_code_exit(char *origin_code, int code_err)
{
	char	*str;

	str = ft_itoa(code_err);
	if (!str)
		return (free(str), free(origin_code), ft_exit(EXIT_FAILURE, true));
	if (ft_strncmp(str, origin_code, ft_len(origin_code)) != 0)
		return (
			ft_printf("Minishell: exit: %s : argument numérique nécessaire\n",
				origin_code), free(str), free(origin_code), ft_exit(2, true));
	code_err = code_err % 256;
	errno = code_err;
	update_err_code(code_err);
	free(origin_code);
	free(str);
	ft_exit(code_err, true);
}

void	exit_prg(char *code_err)
{
	if (ft_len(code_err) > 0 && code_err[0] != '\0')
		update_err_code_exit(code_err, ft_atoi(code_err));
	free(code_err);
}
