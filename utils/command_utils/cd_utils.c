/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/07/06 11:38:21 by tboldrin         ###   ########.fr       */
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
	return (free(result_path), ft_strdup(cd_arg));
}

void	cd_remake(t_cmd_and_opt *cmdopt)
{
	char	path_update[4096];
	char	current_dir[4096];
	char	*tmp_path;
	char	*f;

	if (!cmdopt->opt_ty_tb.tab)
		return ;
	if (d_len(cmdopt->opt_ty_tb.tab) > 2)
		return ((void)update_err_code(1),
		(void)(ft_printf("bash: cd : too many arguments\n")));
	f = special_cara_cd(cmdopt->opt_ty_tb.tab[1]);
	if (!f)
		return ;
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return ((void)update_err_code((int)errno), perror("getcwd"));
	if (chdir(f) == -1)
	{
		ft_printf("bash: cd : \033[31m%s\033[0m: %s\n", f, strerror(errno));
		update_err_code(1);
		free(f);
		return ;
	}
	free(f);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return ((void)update_err_code((int)errno),perror("getcwd"));
	tmp_path = ft_join(ft_strdup("PWD="), get_pwd());
	ft_strlcpy_addr(&path_update, tmp_path, (int)ft_strlen(tmp_path));
	export_var(path_update);
	free(tmp_path);
	return ;
}
