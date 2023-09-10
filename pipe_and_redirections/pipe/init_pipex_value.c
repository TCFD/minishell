/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:07:23 by wolf              #+#    #+#             */
/*   Updated: 2023/09/10 15:08:01 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_fork_opt(t_fork_opt *fork_utils)
{
	fork_utils->cmdopt = NULL;
	fork_utils->str = NULL;
	fork_utils->cmd_id = 0;
}

void	free_fork_opt(t_fork_opt *fork_utils)
{
	free_cmdopt(fork_utils->cmdopt);
	free_d_array(fork_utils->str);
}
