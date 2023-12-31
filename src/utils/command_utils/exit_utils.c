/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:41:50 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/09 16:00:57 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	if_code(char *ipt)
{
	char	*str;

	str = ft_itoa(ft_atoi(ipt));
	if (ft_strncmp(str, ipt, ft_len(ipt)) != 0)
	{
		ft_printf(2, "Minishell: exit: %s : numeric argument required.\n",
			ipt);
		update_err_code(2);
	}
	else
		g_error_code = ft_atoi(ipt);
}

void	check_exit(t_cmd_and_opt *cmdopt)
{
	char	*ipt;

	ipt = NULL;
	if (d_len(cmdopt->opt_ty_tb.tab) > 2 && is_digit(cmdopt->opt_ty_tb.tab[1]))
	{
		return ((void)ft_printf(2, "Minishell: exit: too many arguments."
				"\n"), update_err_code(1));
	}
	if (cmdopt->opt_ty_tb.tab[1])
		ipt = ft_strdup(cmdopt->opt_ty_tb.tab[1]);
	if (!cmdopt->is_child)
	{
		exit_prg(ipt);
		ft_exit(g_error_code, true);
	}
	if (ipt)
		if_code(ipt);
	else
		update_err_code(0);
}

void	ft_exit(int code, bool msg)
{
	if (msg)
	{
		ft_printf(STDOUT_FILENO, "exit\n");
		one_time_animation_end();
	}
	update_pwd(NULL);
	free_garbage();
	exit(code);
}

void	update_err_code_exit(char *origin_code, long long int code_err)
{
	char	*str;

	str = ft_itoa(code_err);
	if (ft_strncmp(str, origin_code, ft_len(origin_code)) != 0)
	{
		ft_printf(2, "Minishell: exit: %s : numeric argument required.\n",
			origin_code);
		return (ft_exit(2, false));
	}
	code_err = code_err % 256;
	errno = code_err;
	update_err_code(code_err);
	ft_exit(code_err, true);
}

void	exit_prg(char *code_err)
{
	char	*tmp;

	if (ft_len(code_err) > 0 && code_err[0] != '\0')
	{
		if (code_err && code_err[0] == '+'
			&& (code_err[1] >= 48 && code_err[1] <= 57))
		{
			tmp = ft_strdup(code_err + 1);
			code_err = tmp;
		}
		update_err_code_exit(code_err, ft_atoi(code_err));
	}
}
