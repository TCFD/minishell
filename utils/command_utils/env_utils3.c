/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:31:23 by wolf              #+#    #+#             */
/*   Updated: 2023/07/03 18:44:50 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	verif_if_env_called(t_cmd_and_opt *cmdopt)
{
	if (cmp(cmdopt->command_path, "/bin/env")
		|| cmp(cmdopt->command_path, "/usr/bin/env")
		|| cmp(cmdopt->command_name, "env"))
		return (1);
	return (0);
}
