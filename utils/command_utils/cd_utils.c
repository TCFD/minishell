/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/08/09 16:47:47 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*special_cara_cd(char *cd_arg)
{
	char	*f;
	char	*path_to_home;
	char	*result_path;
	int		user_in_path;

	if (!cd_arg)
	{
		f = ft_getenv("HOME");
		if (!f)
			return ((void)update_err_code(1),
				ft_printf("bash: cd « HOME » not set\n"), NULL);
		return (ft_strdup(f));
	}
	path_to_home = get_pwd();
	user_in_path = get_word_index(path_to_home, get_username());
	result_path = get_char_until_limit(path_to_home, user_in_path);
	if (cmp(cd_arg, "~"))
		return (result_path);
	if (cmp(cd_arg, "-"))
		return (get_env_var("OLDPWD="));
	return (free(result_path), ft_strdup(cd_arg));
}

char	*join_by_value(char *var_name, char *value)
{
	char	*tmp;

	tmp = ft_join(ft_strdup(var_name), ft_strdup(value));
	return (tmp);
}

void	write_env_oldpwd(t_cd *cd_var, char *oldpwd)
{
	if (cd_var->env_oldpwd_true == 1)
		free(cd_var->env_old_pwd);
	cd_var->env_old_pwd = oldpwd;
	cd_var->env_oldpwd_true = 1;
	export_var(cd_var->env_old_pwd);
}

void	write_env_pwd(t_cd *cd_var, char *pwd)
{
	if (cd_var->env_pwd_true == 1)
		free(cd_var->env_pwd);
	cd_var->env_pwd = pwd;
	cd_var->env_pwd_true = 1;
	export_var(cd_var->env_pwd);
}

void	cd_remake(t_cmd_and_opt *cmdopt)
{
	t_cd	pwd_oldpwd;
	char	current_dir[4096];
	char	*f;

	if (!cmdopt->opt_ty_tb.tab || (d_len(cmdopt->opt_ty_tb.tab) == 2
			&& cmdopt->opt_ty_tb.tab[1][0] == 0))
		return ;
	if (d_len(cmdopt->opt_ty_tb.tab) > 2)
		return ((void)update_err_code(1),
			(void)(ft_printf("bash: cd : too many arguments\n")));
	f = special_cara_cd(cmdopt->opt_ty_tb.tab[1]);
	if (!f)
		return ;
	if (opendir(f) == NULL)
		return ((void)update_err_code((int)errno), 
			(void)printf("bash: cd: can't cd to %s : %s\n", f, strerror(errno)));
	write_env_oldpwd(&pwd_oldpwd, join_by_value("OLDPWD=", current_dir));
	if (chdir(f) == -1)
		return ((void)ft_printf("bash: cd : \033[31m%s\033[0m: %s\n", f, strerror(errno)),
		update_err_code(1), free(f));
	free(f);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return ((void)update_err_code((int)errno),perror("getcwd"));
	write_env_pwd(&pwd_oldpwd, join_by_value("PWD=", current_dir));
	return ;
}
