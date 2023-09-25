/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:36:32 by rciaze            #+#    #+#             */
/*   Updated: 2023/09/22 20:49:44 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// GETENV CHECK
char	*getenv_check(char *str)
{
	char	*found_it;

	found_it = ft_getenv(str);
	if (found_it == NULL)
		return (NULL);
	return (found_it);
}

void	check_to_add_history(char *input)
{
	if (ft_strncmp(get_last_entry(), input,
			ft_strlen(input) + ft_strlen(get_last_entry())))
		add_history(input);
}

int	check_if_pipe(t_opt_tab	opt)
{
	int	i;

	if (!opt.tab)
		return (0);
	i = 0;
	while (opt.tab[i])
	{
		if (opt.tab[i][0] == '|' && opt.type[i] != SIMPLE_Q
		&& opt.type[i] != DOUBLE_Q)
			return (1);
		i++;
	}
	return (0);
}
