/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/23 13:37:19 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_remake(t_cmd_and_opt *cmdopt)
{
	char	current_dir[4096];
	char	*f;

	if (!cmdopt->opt_tab)
		return ;
	if (d_len(cmdopt->opt_tab) > 2)
		return ((void)(ft_printf("bash : cd : too many arguments\n")));
	f = cmdopt->opt_tab[1];
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (perror("getcwd"));
	if (chdir(f) == -1)
	{
		ft_printf("bash : cd : \033[31m%s\033[0m: %s\n", f, strerror(errno));
		return ;
	}
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (perror("getcwd"));
	return ;
}
