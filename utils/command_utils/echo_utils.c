/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:53:45 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/04 16:09:26 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_remake(t_cmd_and_opt *cmdopt)
{
	int		i;
	bool	boolean;

	i = 0;
	if (!ft_strncmp(cmdopt->opt_ty_tb.tab[1], "-n", 
	ft_strlen(cmdopt->opt_ty_tb.tab[1])))
	{
		boolean = true;
		i++;
	}	
	else
		boolean = false;
	while (cmdopt->opt_ty_tb.tab[++i])
	{
		write(STDOUT_FILENO, cmdopt->opt_ty_tb.tab[i], 
		ft_strlen(cmdopt->opt_ty_tb.tab[i]));
		write(STDOUT_FILENO, " ", 1);
	}
	if (boolean == false)
		write(STDOUT_FILENO, "\n", 1);
}
