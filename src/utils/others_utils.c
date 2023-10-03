/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:41:13 by tboldrin          #+#    #+#             */
/*   Updated: 2023/10/03 21:14:25 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heck_if_same(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

char	*get_char_until_limit(char *str, int lim)
{
	char	*new_one;
	int		idx;
	int		b;

	b = 0;
	if (lim < 0)
		b = 1;
	new_one = malloc((lim + b + 1) * sizeof(char));
	if (!new_one)
		return (NULL);
	idx = 0;
	while (idx < lim)
	{
		new_one[idx] = str[idx];
		idx++;
	}
	new_one[idx] = '\0';
	//free(str);
	return (new_one);
}

int	find_first_occurence(char *str, char cara)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == cara)
			return (idx);
		idx++ ;
	}
	return (-1);
}

int	check_if_ifs(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*ft_join(char *s1, char *s2)
{
	char	*new_str;
	int		idx_count;
	int		s1_len;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s1_len = ft_len(s1);
	new_str = malloc((s1_len + ft_len(s2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	idx_count = -1;
	while (++idx_count < s1_len)
		new_str[idx_count] = s1[idx_count];
	idx_count = -1;
	while (++idx_count < ft_len(s2))
		new_str[idx_count + s1_len] = s2[idx_count];
	new_str[idx_count + s1_len] = '\0';
	garbage_add((void *)new_str);
	return (new_str);
}

/*void	add_cmd_to_history_and_run(int check, t_cmd_and_opt *cmdopt,
		char *input, int i)
{
	if (check == 1)
		return (check_to_add_history(input));
	return (loop_it(cmdopt, input, i));
}
*/