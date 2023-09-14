/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:34 by wolf              #+#    #+#             */
/*   Updated: 2023/09/14 16:23:20 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_str(char *str)
{
	free(str);
	str = NULL;
}

void	free_tmp_utils(t_tmp_utils *tmp_utils)
{
	free_str(tmp_utils->l_ety);
	tmp_utils->l_ety = NULL;
	free_str(tmp_utils->prompt);
	tmp_utils->prompt = NULL;
}
