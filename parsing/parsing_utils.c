/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:49:13 by wolf              #+#    #+#             */
/*   Updated: 2023/08/09 16:45:23 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (ft_strdup(""));
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

int	check_valid_file_name(char **t, char *type)
{
	int	i;

	i = -1;
	while (t[++i])
	{
		if ((ft_strnstr(t[i], S_R_RAFTER, ft_strlen(t[i]))
				|| ft_strnstr(t[i], S_L_RAFTER, ft_strlen(t[i])))
			&& type[i] != SIMPLE_Q && type[i] != DOUBLE_Q)
		{
			if ((!t[i + 1]
					|| ft_strnstr(t[i + 1], S_L_RAFTER, ft_strlen(t[i + 1]))
					|| ft_strnstr(t[i + 1], S_R_RAFTER, ft_strlen(t[i + 1]))
					|| ft_strnstr(t[i + 1], PIPE, ft_strlen(t[i + 1])))
				&& type[i + 1] != SIMPLE_Q && type[i + 1] != DOUBLE_Q)
			{
				if (t[i + 1])
					return (printf("minishell : syntax error near unexpected"
							"token '%s'\n", t[i + 1]));
				return (printf("minishell : syntax error near unexpected"
						"token 'newline'\n"));
			}
		}
	}
	return (0);
}
