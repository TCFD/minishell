/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:53:45 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/22 15:07:06 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_remake(t_cmd_and_opt *cmdopt)
{
	int		i;
	bool	boolean;

	i = 0;
	if (!ft_strncmp(cmdopt->option.opt_tab[1], "-n", ft_strlen(cmdopt->option.opt_tab[1])))
	{
		boolean = true;
		i++;
	}	
	else
		boolean = false;
	while (cmdopt->option.opt_tab[++i])
		write(1, cmdopt->option.opt_tab[i], ft_strlen(cmdopt->option.opt_tab[i]));
	if (boolean == false)
		write(1, "\n", 1);
}