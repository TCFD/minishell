/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/07/05 12:27:16 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*special_cara_cd(char *cd_arg)
{
	char	*f;

	if (!cd_arg)
	{
		f = ft_getenv("HOME");
		if (!f)
			return ((void)update_err_code(1), 
			ft_printf("bash: cd « HOME » not set\n"), NULL);
		return (ft_strdup(f));
	}
	if (cmp(cd_arg, "~"))
		return (ft_join(ft_strdup("/home/"), ft_strdup(get_username())));
	return (ft_strdup(cd_arg));
}

void	cd_remake(t_cmd_and_opt *cmdopt)
{
	char	current_dir[4096];
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
	return ;
}
