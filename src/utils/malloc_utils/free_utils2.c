/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:34 by wolf              #+#    #+#             */
/*   Updated: 2023/09/28 19:02:48 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	malloc_fail(void)
{
	perror("Critical error: (malloc probably failed)");
	ft_exit(EXIT_FAILURE, true);
}