/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:41:38 by wolf              #+#    #+#             */
/*   Updated: 2023/06/21 12:21:42 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_str(char *str, char *cut)
{
	char	new_str[1064];
	int		idx;
	int		sub_idx;
	int		sub_total;

	idx = 0;
	sub_idx = 0;
	sub_total = 0;
	while (str[idx])
	{
		if (str[idx] == cut[0])
		{
			sub_idx = 1;
			while (str[idx + sub_idx] == cut[sub_idx])
				sub_idx++ ;
			idx += sub_idx;
			sub_total += sub_idx;
		}
		new_str[idx - sub_total] = str[idx];
	}
	return (new_str);
}

/////// A CONTINUER
char	**create_pipex_cmd(char *command)
{
	char	**buble_cmd;

	return (NULL);
}

char	*find_infile(char *first_command)
{
	char	**f_cmd_split;
	char	*infile;
	int		idx;

	f_cmd_split = ft_split(first_command, ' ');
	idx = 1;
	while (idx < d_len(f_cmd_split))
	{
		if (!ft_strchr(f_cmd_split, '-'))
		{
			infile = ft_cpy(f_cmd_split[idx], 0);
			return (free_d_array(f_cmd_split), infile);
		}
		idx++ ;
	}
	return (NULL);
}

int	use_pipex(char *command)
{
	char	**command_split;
	char	*infile;

	if (!ft_strchr(command, '|'))
		return (0);
	command_split = ft_split(command, '|');
	infile = find_infile(command_split[0]);
	return (1);
}
