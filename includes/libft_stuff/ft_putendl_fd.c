/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:18:40 by tboldrin          #+#    #+#             */
/*   Updated: 2022/11/21 16:20:50 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++ ;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	char	n;

	n = '\n';
	ft_putstr_fd(s, fd);
	write(fd, &n, 1);
}
