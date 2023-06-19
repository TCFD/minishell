/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:58:08 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/19 19:24:01 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_remake(t_cmd_and_opt *cmdopt)
{
	char	current_dir[4096];
	char	*f;

	if (!cmdopt->option)
		return ;
	if (d_len(cmdopt->option) > 2)
		return ((void)(ft_printf("bash : cd : too many arguments\n")));
	f = cmdopt->option[1];
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