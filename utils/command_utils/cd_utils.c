/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/08/23 16:14:59 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*special_cara_cd(char *cd_arg)
{
	char	*f;
	char	*path_to_home;

	if (!cd_arg)
	{
		f = ft_getenv("HOME");
		if (!f)
			return ((void)update_err_code(1),
				ft_printf("Minishell: cd « HOME » not set\n"), NULL);
		return (f);
	}
	path_to_home = get_home_path();
	if (cmp(cd_arg, "~"))
		return (path_to_home);
	if (cmp(cd_arg, "-"))
		return (get_env_var("OLDPWD="));
	// peut-etre cd_arg a free
	return (cd_arg);
}

char	*join_by_value(char *var_name, char *value)
{
	char	*tmp;

	tmp = ft_join(ft_strdup(var_name), ft_strdup(value));
	return (tmp);
}

void	write_env_oldpwd(char *oldpwd)
{
	update_env_oldpwd(oldpwd);
	export_var(get_env_oldpwd());
}

void	write_env_pwd(char *pwd)
{
	update_env_pwd(pwd);
	export_var(get_env_pwd());
}

char	*get_opendir_value(t_cmd_and_opt *cmdopt)
{
	bool	is_malloc;
	char	*f;
	char	*tmp_name;
	DIR		*file;
	
	is_malloc = false;
	f = special_cara_cd(cmdopt->opt_ty_tb.tab[1]);
	if (!f)
		return (NULL);
	tmp_name = f;
	if ('~' == f[0])
	{
		is_malloc = true;
		f = ft_join(ft_strdup(get_home_path()), ft_strdup(f + 1));
		file = opendir(f);
	}
	else
		file = opendir(f);
	if (file == NULL && is_malloc == true)
		free(f);
	if (file == NULL)
		return (closedir(file), (void)update_err_code((int)errno), 
			(void)ft_printf("Minishell: cd: %s: %s\n", tmp_name, strerror(errno)),
			NULL);
	closedir(file);
	//if (cmp("~", cmdopt->opt_ty_tb.tab[1])
	//	|| (cmdopt->opt_ty_tb.tab[1] && ('~' == cmdopt->opt_ty_tb.tab[1][0])))
	//	return ((void)printf("yup\n"), f);
	if (is_malloc == true)
		return (f);
	return (ft_strdup(f));
}

void	cd_remake(t_cmd_and_opt *cmdopt)
{
	char	current_dir[4096];
	char	*pwd_path;
	char	*f;

	current_dir[0] = '\0';
	if (!cmdopt->opt_ty_tb.tab || (d_len(cmdopt->opt_ty_tb.tab) == 2
			&& cmdopt->opt_ty_tb.tab[1][0] == 0))
		return ;
	if (d_len(cmdopt->opt_ty_tb.tab) > 2)
		return ((void)update_err_code(1),
			(void)(ft_printf("Minishell: cd : too many arguments\n")));
	f = get_opendir_value(cmdopt);
	if (f == NULL)
		return ;
	pwd_path = get_pwd();
	write_env_oldpwd(join_by_value("OLDPWD=", pwd_path));
	free(pwd_path);
	if (chdir(f) == -1)
		return ((void)ft_printf("Minishell: cd : \033[31m%s\033[0m: %s\n",
			f, strerror(errno)), update_err_code(1), free(f));
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return ((void)update_err_code((int)errno),perror("getcwd"), free(f));
	write_env_pwd(join_by_value("PWD=", current_dir));
	return (free(f));
}
