/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:49:13 by wolf              #+#    #+#             */
/*   Updated: 2023/08/08 19:15:18 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// CREATE OPTIONS
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
			return (free(all_options), NULL);
		idx++ ;
	}
	all_options[idx + 1] = NULL;
	return (all_options);
}

// IS PATH UNSET
char	*is_path_unset(char *command_name, int imd_return)
{
	char	**path_split;
	char	*env_path;
	char	*path;
	char	*path2;
	int		idx;

	env_path = ft_getenv("PATH");
	if (!env_path && imd_return)
		return (ft_strdup(command_name));
	if (env_path)
		path_split = ft_split(env_path, ':');
	else
		path_split = ft_split(ft_strdup("/bin/usr:/bin"), ':');
	idx = 0;
	while (idx < d_len(path_split))
	{
		path = ft_join(ft_strdup(path_split[idx]), ft_strdup("/"));
		path2 = ft_join(path, ft_strdup(command_name));
		if (access(path2, F_OK | X_OK) == 0)
			return ((free_d_array(path_split)), path2);
		free(path2);
		idx++ ;
	}
	free_d_array(path_split);
	return (ft_strdup(command_name));
}

// DOES COMMAND PATH VALID
int	does_command_path_valid(char *cmd)
{
	char	**path_split;
	char	*env_path;
	char	*path;
	char	*path2;
	int		idx;

	env_path = ft_getenv("PATH");
	if (!env_path)
		return (0);
	path_split = ft_split(env_path, ':');
	idx = 0;
	while (idx < d_len(path_split))
	{
		path = ft_join(ft_strdup(path_split[idx]), ft_strdup("/"));
		path2 = ft_join(path, ft_strdup(cmd));
		if (access(path2, F_OK | X_OK) == 0)
			return ((free(cmd)), (free_d_array(path_split), free(path2)), 1);
		free(path2);
		idx++ ;
	}
	free_d_array(path_split);
	return (0);
}

// CREATE PATH
char	*create_path(char *command_name, int imd_return)
{	
	if (ft_strchr(command_name, '/'))
		return (ft_strdup(command_name));
	return (is_path_unset(command_name, imd_return));
}

// CREATE COMMAND
void	create_command(char	*input, t_cmd_and_opt *cmdopt)
{
	if (!input[0])
		return ;
	if (!check_correct_quotes(input))
		return ((void)(printf("minishell : incorect quotes.\n")));
	interpret_quotes(input, cmdopt, 0);
	if (cmdopt->path_unset == 0 && !ft_getenv("PATH"))
	{
		cmdopt->command_name = create_path(cmdopt->opt_ty_tb.tab[0], 0);
		cmdopt->command_path = ft_cpy(cmdopt->command_name, 0);
	}
	else
	{
		cmdopt->command_name = brut_name(cmdopt->opt_ty_tb.tab[0]);
		cmdopt->command_path = create_path(cmdopt->opt_ty_tb.tab[0], 1);
	}
	free(cmdopt->opt_ty_tb.tab[0]);
	cmdopt->opt_ty_tb.tab[0] = ft_strdup(cmdopt->command_path);
}
