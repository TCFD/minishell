/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:04:45 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 14:23:47 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*current_dir;
	char	*last_one;

	last_one = get_pwd_path();
	current_dir = get_env_var("PWD=");
	if (current_dir != NULL)
		return (update_pwd(ft_strdup(current_dir))
			, current_dir);
	current_dir = ft_malloc(1024);
	//garbage_add((void *)current_dir);
	if (getcwd(current_dir, 1024) == NULL)
		return (free(current_dir),
			ft_strdup(last_one));
	update_err_code(0);
	last_one = ft_cpy(current_dir, 0);
	//garbage_add((void *)last_one);
	update_pwd(last_one);
	return (current_dir);
}

char	*get_pwd_for_pwd(void)
{
	char	*current_dir;
	char	*last_one;

	last_one = get_pwd_path();
	current_dir = get_env_var("PWD=");
	if (current_dir != NULL)
		return ((update_err_code(0)), update_pwd(current_dir),
			ft_strdup(current_dir));
	current_dir = ft_malloc(1024);
	if (getcwd(current_dir, 1024) == NULL)
		return (free(current_dir), update_err_code(0),
			ft_strdup(last_one));
	update_err_code(0);
	last_one = ft_cpy(current_dir, 0);
	update_pwd(last_one);
	return (current_dir);
}

void	print_pwd(void)
{
	char	*pwd_print;

	pwd_print = get_pwd_for_pwd();
	if (pwd_print == NULL)
		pwd_print = get_pwd_path();
	ft_printf(STDOUT_FILENO, "%s\n", pwd_print);
	free(pwd_print);
}
