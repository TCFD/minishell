/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_fail_version_beta.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:39:59 by wolf              #+#    #+#             */
/*   Updated: 2023/09/28 20:30:18 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_no_strdup(char *s1, char *s2)
{
	char	*str;

	str = ft_join(s1, s2);
	if (!str)
		return (ft_exit(EXIT_FAILURE, false), NULL);
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
	if (!s1_strdup)
		return (NULL);
	s2_strdup = ft_strdup(s2);
	if (!s2_strdup)
		return (free(s1_strdup), NULL);
	var_join_strdup = ft_join(s1_strdup, s2_strdup);
	if (!var_join_strdup)
		return (NULL);
	return (var_join_strdup);
}

char	*ft_join_strdup_right(char *s1, char *s2)
{
	char	*s2_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s2_strdup = ft_strdup(s2);
	if (!s2_strdup)
		return (NULL);
	var_join_strdup = ft_join(s1, s2_strdup);
	if (!var_join_strdup)
		return (NULL);
	return (var_join_strdup);
}

char	*ft_join_strdup_left(char *s1, char *s2)
{
	char	*s1_strdup;
	char	*var_join_strdup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_strdup = ft_strdup(s1);
	if (!s1_strdup)
		return (NULL);
	var_join_strdup = ft_join(s1_strdup, s2);
	if (!var_join_strdup)
		return (NULL);
	return (var_join_strdup);
}
