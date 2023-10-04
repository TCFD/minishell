/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:34 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 14:22:24 by rciaze           ###   ########.fr       */
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
	perror("Critical error: (ft_malloc probably failed)");
	ft_exit(EXIT_FAILURE, true);
}

void	free_dollar(t_dollar *dollar)
{
	free(dollar->tmp_dup);
	free(dollar->env_var);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		malloc_failure();
	garbage_add(ptr);
	return (ptr);
}