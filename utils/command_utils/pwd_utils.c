/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:04:45 by wolf              #+#    #+#             */
/*   Updated: 2023/08/07 19:19:59 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_pwd(void)
{
	char	*current_dir;

	current_dir = malloc(1024);
	if (getcwd(current_dir, 1024) == NULL)
		return (free(current_dir), (void)update_err_code((int)errno),
			(void)perror("getcwd"), NULL);
	update_err_code(0);
	return (current_dir);
}

void	print_pwd(void)
{
	char	*pwd_print;

	pwd_print = get_pwd();
	ft_printf("%s\n", pwd_print);
	free(pwd_print);
}
