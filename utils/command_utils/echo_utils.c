/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:53:45 by rciaze            #+#    #+#             */
/*   Updated: 2023/08/07 19:14:23 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_n(t_cmd_and_opt *cm, int *i, int *j, bool *boolean)
{
	bool	temp_boolean;

	if (cm->opt_ty_tb.tab[1] && !ft_strncmp(cm->opt_ty_tb.tab[1], "-n", 2))
	{
		temp_boolean = true;
		*boolean = false;
		*i += 1;
		while (!ft_strncmp(cm->opt_ty_tb.tab[*i], "-n", 2)
			&& temp_boolean == true && cm->opt_ty_tb.tab[*i])
		{
			while (cm->opt_ty_tb.tab[*i][*j]
				&& cm->opt_ty_tb.tab[*i][*j] == 'n')
				*j += 1;
			if (cm->opt_ty_tb.tab[*i][*j] && cm->opt_ty_tb.tab[*i][*j] != 'n')
				temp_boolean = false;
			else
			{
				if (*i == 1)
					*boolean = true;
				*i += 1;
			}
			*j = 1;
		}
		*i -= 1;
	}
}

void	echo_remake(t_cmd_and_opt *cm)
{
	int		i;
	int		j;
	bool	boolean;

	j = 1;
	i = 0;
	boolean = false;
	skip_n(cm, &i, &j, &boolean);
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
