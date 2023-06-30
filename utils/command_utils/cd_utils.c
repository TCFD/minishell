/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/30 19:04:32 by zbp15            ###   ########.fr       */
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
			return (ft_printf("bash: cd « HOME » not set\n"), NULL);
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

	if (!cmdopt->opt_tab.tab)
		return ;
	if (d_len(cmdopt->opt_tab.tab) > 2)
		return ((void)(ft_printf("bash: cd : too many arguments\n"))); // modifier la valeur errno (appeler une fonction avec msg erreur)
	f = special_cara_cd(cmdopt->opt_tab.tab[1]);
	if (!f)
		return ;
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (perror("getcwd"));
	if (chdir(f) == -1)
	{
		ft_printf("bash: cd : \033[31m%s\033[0m: %s\n", f, strerror(errno));
		free(f);
		return ;
	}
	free(f);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (perror("getcwd"));
	return ;
}
