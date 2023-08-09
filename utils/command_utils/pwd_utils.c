/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:04:45 by wolf              #+#    #+#             */
/*   Updated: 2023/08/09 16:49:08 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_pwd(void)
{
	char	*current_dir;
	
	current_dir = get_env_var("PWD=");
	if (current_dir != NULL)
		return ((update_err_code(0)), update_pwd(current_dir), ft_strdup(current_dir));
	current_dir = malloc(1024);
	if (getcwd(current_dir, 1024) == NULL)
		return (free(current_dir), (void)update_err_code((int)errno),
			(void)perror("getcwd"), NULL);
	update_err_code(0);
	update_pwd(current_dir);
	return (current_dir);
}

void	print_pwd(void)
{
	char	*pwd_print;

	pwd_print = get_pwd();
	ft_printf("%s\n", pwd_print);
	free(pwd_print);
}
