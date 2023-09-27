/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/09/27 10:22:05 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*special_cara_cd(char *cd_arg)
{
	char	*f;
	char	*path_to_home;

	if (!cd_arg)
	{
		f = ft_getenv("HOME");
		if (!f)
			return ((void)update_err_code(1),
				ft_printf(2, "Minishell: cd « HOME » not set\n"), NULL);
		return (f);
	}
	path_to_home = get_home_path();
	if (cmp(cd_arg, "~"))
		return (path_to_home);
	if (cmp(cd_arg, "-"))
		return (get_env_var("OLDPWD="));
	return (cd_arg);
}
// peut-etre cd_arg a free

char	*get_opendir_value(t_cmd_and_opt *cmdopt, bool is_malloc, DIR *file)
{
	char	*f;

	f = special_cara_cd(cmdopt->opt_ty_tb.tab[1]);
	if (!f)
		return (NULL);
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
		return ((void)ft_printf(2, "Minishell: cd: %s\n",
				"No such file or directory"),
			closedir(file), (void)update_err_code((int)errno),
			NULL);
	closedir(file);
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
			(void)(ft_printf(2, "Minishell: cd : too many arguments\n")));
	f = get_opendir_value(cmdopt, false, NULL);
	if (f == NULL)
		return ;
	pwd_path = get_pwd();
	write_env_oldpwd(join_by_value("OLDPWD=", pwd_path));
	free(pwd_path);
	if (chdir(f) == -1)
		return ((void)ft_printf(2, "Minishell: cd : \033[31m%s\033[0m: %s\n",
				f, strerror(errno)), update_err_code(1), free(f));
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return ((void)update_err_code((int)errno), perror("getcwd"), free(f));
	write_env_pwd(join_by_value("PWD=", current_dir));
	return (free(f));
}
