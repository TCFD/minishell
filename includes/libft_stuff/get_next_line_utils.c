/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:53:57 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/04 14:21:59 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/minishell.h"

/////// NEW BUFF STATIC ****
void	new_buff_static(char **static_buff, int idx_null_cara)
{
	char	*new_one;

	if (static_buff[0][idx_null_cara + 1] == '\0')
	{
		free(*static_buff);
		*static_buff = malloc_fill("");
		return ;
	}
	new_one = ft_cpy(*static_buff + idx_null_cara + 1, 0);
	free(*static_buff);
	*static_buff = ft_cpy(new_one, 1);
}

/////// OUTPUT_RESULT ****
char	*output_result(char **static_buff, int idx_null_cara)
{
	char	*final_result;
	int		idx_start;

	final_result = ft_malloc((idx_null_cara + 2) * sizeof(char));
	if (!final_result)
		return (NULL);
	idx_start = 0;
	while (idx_start <= idx_null_cara)
	{
		final_result[idx_start] = static_buff[0][idx_start];
		idx_start++ ;
	}
	final_result[idx_start] = '\0';
	new_buff_static(static_buff, idx_null_cara);
	return (final_result);
}

/////// READ FD
char	*read_fd(int fd, int *verification, char **static_buff)
{
	char	*buff_tmp;
	char	*new_s_buff;
	char	*cpy_tmp;
	int		result_read;

	buff_tmp = ft_malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff_tmp)
		return (NULL);
	result_read = read(fd, buff_tmp, BUFFER_SIZE);
	*verification = result_read;
	if (result_read && result_read > 0)
	{
		buff_tmp[result_read] = '\0';
		cpy_tmp = ft_strdup(*static_buff);
		new_s_buff = ft_join(cpy_tmp, buff_tmp);
		*static_buff = ft_strdup(new_s_buff);
		return (*static_buff);
	}
	free(buff_tmp);
	return (NULL);
}

/////// MAIN CODE ----
char	*main_code(int fd)
{
	static char	*buff_static;
	char		*output;
	int			idx_null_cara;
	int			count;

	count = 1;
	if (!buff_static)
		buff_static = malloc_fill("");
	while (count)
	{
		idx_null_cara = null_cara_found(buff_static);
		if (idx_null_cara != -1)
			return (output_result(&buff_static, idx_null_cara));
		if (!read_fd(fd, &count, &buff_static))
			break ;
	}
	output = ft_cpy(buff_static, 1);
	buff_static = NULL;
	if (ft_len(output) != 0)
		return (output);
	free(output);
	return (buff_static);
}
