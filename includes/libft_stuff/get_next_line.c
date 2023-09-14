/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:50:17 by tboldrin          #+#    #+#             */
/*   Updated: 2023/06/23 15:04:43 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

////// GET NEXT LINE ----
char	*get_next_line(int fd)
{
	char	*result;

	if (fd == -1)
		return (NULL);
	result = main_code(fd);
	return (result);
}

////// FT LEN ----
int	ft_len(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count])
		count++ ;
	return (count);
}

////// MALLOC && FILL ----
char	*malloc_fill(char *content)
{
	char	*result;
	int		idx;

	result = malloc((1 + ft_len(content)) * sizeof(char));
	if (!result)
		return (NULL);
	idx = 0;
	while (content[idx])
	{
		result[idx] = content[idx];
		idx++ ;
	}
	result[idx] = '\0';
	return (result);
}

/////// NULL CARA FOUND ----
int	null_cara_found(char *static_buff)
{
	int		idx_static_buff;

	idx_static_buff = 0;
	while (static_buff[idx_static_buff])
	{
		if (static_buff[idx_static_buff] == '\n')
			return (idx_static_buff);
		idx_static_buff++ ;
	}
	return (-1);
}

/////// FT CPY
char	*ft_cpy(const char *what_to_cpy, int possible_to_free)
{
	char	*cpy_out;
	int		size;
	int		count;

	size = ft_len((char *)what_to_cpy);
	cpy_out = malloc((size + 1) * sizeof(char));
	if (!cpy_out)
		return (NULL);
	count = 0;
	while (what_to_cpy[count] && count < size)
	{
		cpy_out[count] = what_to_cpy[count];
		count++ ;
	}
	cpy_out[count] = '\0';
	if (possible_to_free)
		free((char *)what_to_cpy);
	return (cpy_out);
}
