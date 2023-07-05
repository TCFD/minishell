/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:04:45 by wolf              #+#    #+#             */
/*   Updated: 2023/07/05 12:22:11 by wolf             ###   ########.fr       */
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
