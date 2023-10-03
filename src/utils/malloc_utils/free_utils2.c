/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:34 by wolf              #+#    #+#             */
/*   Updated: 2023/10/03 15:57:50 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	malloc_failure(void)
{
	perror("Critical error: (malloc probably failed)");
	ft_exit(EXIT_FAILURE, true);
}

void	free_dollar(t_dollar *dollar)
{
	free(dollar->tmp_dup);
	free(dollar->env_var);
}
