/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:41:50 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/27 10:54:18 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	if_code(char *ipt)
{
	char	*str;

	str = ft_itoa(ft_atoi(ipt));
	if (ft_strncmp(str, ipt, ft_len(ipt)) != 0)
	{
		ft_printf(2, "exit\nMinishell: exit: %s : numeric argument required.\n",
			ipt);
		update_err_code(2);
	}
	else
		g_error_code = ft_atoi(ipt);
	free(ipt);
	free(str);
}

void	check_exit(t_cmd_and_opt *cmdopt)
{
	char	*ipt;

	ipt = NULL;
	if (d_len(cmdopt->opt_ty_tb.tab) > 2 && not_digit(cmdopt->opt_ty_tb.tab[1]))
		return ((void)ft_printf(2, "exit\nMinishell: exit: too many arguments."
				"\n"), update_err_code(1));
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
		//one_time_animation_end();
	}
	update_pwd(NULL);
	free(get_env_pwd());
	free(get_env_oldpwd());
	free(get_home_path());
	free(get_username());
	free_prompt_last_entry();
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
	{
		ft_printf(2, "exit\nMinishell: exit: %s : numeric argument required.\n",
			origin_code);
		if (origin_code)
			free(origin_code);
		return (free(str), ft_exit(2, false));
	}
	code_err = code_err % 256;
	errno = code_err;
	update_err_code(code_err);
	if (origin_code)
		free(origin_code);
	free(str);
	ft_exit(code_err, true);
}

void	exit_prg(char *code_err)
{
	if (ft_len(code_err) > 0 && code_err[0] != '\0')
		update_err_code_exit(code_err, ft_atoi(code_err));
	if (code_err)
		free(code_err);
}
