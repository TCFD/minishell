/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_fail_version_beta.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:39:59 by wolf              #+#    #+#             */
/*   Updated: 2023/10/04 14:19:46 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_no_strdup(char *s1, char *s2)
{
	char	*str;

	str = ft_join(s1, s2);
	return (str);
}

char	*ft_join_strdup(char *s1, char *s2)
{
	char	*s1_strdup;
	char	*s2_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_strdup = ft_strdup(s1);
	s2_strdup = ft_strdup(s2);
	var_join_strdup = ft_join(s1_strdup, s2_strdup);
	return (var_join_strdup);
}

char	*ft_join_strdup_right(char *s1, char *s2)
{
	char	*s2_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s2_strdup = ft_strdup(s2);
	var_join_strdup = ft_join(s1, s2_strdup);
	return (var_join_strdup);
}

char	*ft_join_strdup_left(char *s1, char *s2)
{
	char	*s1_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_strdup = ft_strdup(s1);
	var_join_strdup = ft_join(s1_strdup, s2);
	return (var_join_strdup);
}
