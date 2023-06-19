/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:49:13 by wolf              #+#    #+#             */
/*   Updated: 2023/06/19 18:25:38 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_options(char *cmd_name, char **all_args)
{
	char	**all_options;
	int		idx;

	all_options = malloc((d_len(all_args) + 2) * sizeof(char *));
	if (!all_options)
		return (NULL);
	all_options[0] = ft_strdup(cmd_name);
	if (!all_options[0])
		return (free(all_options), NULL);
	idx = 0;
	while (idx < d_len(all_args))
	{
		all_options[idx + 1] = ft_strdup(all_args[idx]);
		if (!all_options[idx + 1])
			return (free(all_options), (free(all_options[idx + 1])), NULL);
		idx++ ;
	}
	all_options[idx + 1] = NULL;
	return (all_options);
}

char	*is_path_unset(char *command_name)
{
	char	**path_split;
	char	*env_path;
	char	*path;
	char	*path2;
	int		idx;

	env_path = getenv("PATH");
	if (!env_path)
		return (command_name);
	path_split = ft_split(env_path, ':');
	idx = 0;
	while (idx < d_len(path_split))
	{
		path = ft_join(ft_strdup(path_split[idx]), ft_strdup("/"));
		path2 = ft_join(path, ft_strdup(command_name));
		if (access(path2, F_OK | X_OK) == 0)
			return ((free(command_name)), (free_d_array(path_split)), path2);
		free(path2);
		idx++ ;
	}
	free_d_array(path_split);
	return (command_name);
}

char	*create_path(char *command_name)
{	
	if (ft_strchr(command_name, '/'))
		return (command_name);
	return (is_path_unset(command_name));
}

void	create_command(char	*input, t_cmd_and_opt *cmdopt)
{
	char	**all_args;
	
	if (!input[0])
		return ;
	all_args = ft_split(input, ' ');
	cmdopt->command_name = brut_name(ft_strdup(all_args[0]));
	cmdopt->command_path = create_path(ft_strdup(all_args[0]));
	if (all_args[1])
		cmdopt->option = create_options(cmdopt->command_name, all_args + 1);
	return (free_d_array(all_args));
}
