/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:49:13 by wolf              #+#    #+#             */
/*   Updated: 2023/07/07 14:12:01 by rciaze           ###   ########.fr       */
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
		return (command_name);
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
			return ((free(command_name)), (free_d_array(path_split)), path2);
		free(path2);
		idx++ ;
	}
	free_d_array(path_split);
	return (command_name);
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
		return (command_name);
	return (is_path_unset(command_name, imd_return));
}

int	check_valid_file_name(t_cmd_and_opt *cmdopt)
{
	int	i;

	i = -1;
	while (cmdopt->opt_ty_tb.tab[++i])
	{
		if (ft_strncmp(cmdopt->opt_ty_tb.tab[i], SIMPLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i]))
			|| ft_strncmp(cmdopt->opt_ty_tb.tab[i], DOUBLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i])))
		{
			if (!cmdopt->opt_ty_tb.tab[i + 1][0]
			|| ft_strncmp(cmdopt->opt_ty_tb.tab[i + 1], SIMPLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i + 1]))
			|| ft_strncmp(cmdopt->opt_ty_tb.tab[i + 1], DOUBLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i + 1]))
			|| ft_strncmp(cmdopt->opt_ty_tb.tab[i + 1], PIPE,
			ft_strlen(cmdopt->opt_ty_tb.tab[i + 1])))
			{
				if (cmdopt->opt_ty_tb.tab[i + 1])
					return (printf("minishell : syntax error near unexpected token '%s'\n", cmdopt->opt_ty_tb.tab[i + 1]));
				return (printf("minishell : syntax error near unexpected token 'newline'\n"));
			}
		}
	}
}

// CREATE COMMAND
void	create_command(char	*input, t_cmd_and_opt *cmdopt)
{
	if (!input[0])
		return ;
	if (!check_correct_quotes(input))
		return ((void)(printf("minishell : incorect quotes.\n")));
	parse_that_shit(input, cmdopt);
	if (check_valid_file_name(cmdopt))
		return ;
	int i = -1;
	while (cmdopt->opt_ty_tb.tab[++i])
		printf("option '%s', type = %c\n", cmdopt->opt_ty_tb.tab[i], cmdopt->opt_ty_tb.type[i]);
	printf("\n\n");
	if (cmdopt->path_unset == 0 && !ft_getenv("PATH"))
	{
		cmdopt->command_name = create_path(ft_strdup(cmdopt->opt_ty_tb.tab[0]), 0);
		cmdopt->command_path = ft_cpy(cmdopt->command_name, 0);
	}
	else
	{
		cmdopt->command_name = brut_name(ft_strdup(cmdopt->opt_ty_tb.tab[0]));
		cmdopt->command_path = create_path(ft_strdup(cmdopt->opt_ty_tb.tab[0]), 1);
	}
	free(cmdopt->opt_ty_tb.tab[0]);
	cmdopt->opt_ty_tb.tab[0] = ft_strdup(cmdopt->command_path);
}
