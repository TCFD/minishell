/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:37:54 by zbp15             #+#    #+#             */
/*   Updated: 2023/06/30 18:38:05 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_chevrons(char **input, int end)
{
	long int	simple_chevrons;
	long int	chevrons;
	char		*tmp;
	int			one_or_two_quotes;

	chevrons = ft_strnstr(*input, ">>", ft_strlen(*input)) - *input;
	if (chevrons < 0)
		chevrons = ft_strlen(*input);
	one_or_two_quotes = 2;
	simple_chevrons = ft_strnstr(*input, ">", ft_strlen(*input)) - *input;
	if (simple_chevrons < chevrons && input[0][simple_chevrons + 1] != '>')
	{
		chevrons = simple_chevrons;	
		one_or_two_quotes = 1;
	}
	if ((input[0][chevrons + one_or_two_quotes] != ' ' || input[0][chevrons - 1] != ' ') && chevrons < end)
	{
		tmp = ft_substr(*input, 0, chevrons - (one_or_two_quotes / 2));
		if (tmp[0])
			tmp = ft_join(tmp, ft_strdup(" "));
		tmp = ft_join(tmp, ft_substr(*input, chevrons - (one_or_two_quotes / 2), one_or_two_quotes));
		tmp = ft_join(tmp, ft_strdup(" "));
		tmp = ft_join(tmp, ft_substr(*input, chevrons + 1, ft_strlen(*input)));
		return(tmp);
	}
	return (*input);
}