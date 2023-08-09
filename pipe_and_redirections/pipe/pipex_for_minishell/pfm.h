/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:04:59 by wolf              #+#    #+#             */
/*   Updated: 2023/07/14 18:13:00 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_pipes
{
    int **pipes;
    int *pids;
    int len_max;
    int idx;
}t_pipes;



void	pipex(char *input);