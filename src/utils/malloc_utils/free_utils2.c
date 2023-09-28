/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:34 by wolf              #+#    #+#             */
/*   Updated: 2023/09/28 14:01:12 by rciaze           ###   ########.fr       */
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