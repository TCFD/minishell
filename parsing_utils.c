/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:49:13 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 15:36:56 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_options(char **all_args)
{
	char	**all_options;
	int		idx;

	all_options = malloc((d_len(all_args) + 1) * sizeof(char *));
	if (!all_options)
		return (NULL);
	idx = 0;
	while (idx < d_len(all_args))
	{
		all_options[idx] = malloc((ft_strlen(all_args[idx]) + 1) * sizeof(char));
		if (!all_options[idx])
			return (NULL);
		all_options[idx] = ft_cpy(all_args[idx], 1);
		idx++ ;
	}
	all_options[idx] = NULL;
	return (all_options);
}

void	create_command(char	*input, t_cmd_and_opt *cmdopt)
{
	char	**all_args;
	
	if (!input[0])
		return ;
	all_args = ft_split(input, ' ');
	cmdopt->command_name = all_args[0];
	if (all_args[1])
		cmdopt->option = create_options(all_args + 1);
	free(all_args);
}
