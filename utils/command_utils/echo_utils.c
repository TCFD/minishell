/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:53:45 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/13 17:17:05 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_remake(t_cmd_and_opt *cm)
{
	int		i;
	int		j;
	bool	boolean;

	j = 1;
	i = 0;
	boolean = false;
	if (!ft_strncmp(cm->opt_ty_tb.tab[1], "-n", 2))
	{
		while (cm->opt_ty_tb.tab[1][++j] && cm->opt_ty_tb.tab[1][j] == 'n')
			boolean = true;
		if (cm->opt_ty_tb.tab[1][j] && cm->opt_ty_tb.tab[1][j] != 'n')
			boolean = false;
		else
			i += 1;
	}
	while (cm->opt_ty_tb.tab[++i])
	{
		write(STDOUT_FILENO, cm->opt_ty_tb.tab[i],
			ft_strlen(cm->opt_ty_tb.tab[i]));
		if (cm->opt_ty_tb.tab[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (boolean == false)
		write(STDOUT_FILENO, "\n", 1);
}
