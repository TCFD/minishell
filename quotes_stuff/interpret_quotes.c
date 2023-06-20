/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:06:57 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/20 15:24:46 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	which_one(char *input)
{
	char	*first_simple_quote;
	char	*first_double_quote;
	char	*first_space;

	first_simple_quote = ft_strchr(input, '\'');
	first_double_quote = ft_strchr(input, '\"');
	first_space = ft_strchr(input, ' ');
	if (first_simple_quote == input)
		first_simple_quote = input + ft_strlen(input);
	if (first_double_quote == input)
		first_double_quote = input + ft_strlen(input);
	if (first_space == input)
		first_space = input + ft_strlen(input);
	if (first_space < first_double_quote && first_space < first_simple_quote)
		return (SPACE);
	if (first_simple_quote < first_double_quote)
		return (SIMPLE_Q);
	if (first_simple_quote > first_double_quote)
		return (DOUBLE_Q);
	return ('\0');
}

void	words(char **input, char what_case, char **dest, bool *boolean)
{
	long int	first_quote;
	long int	second_quote;
	long int	final_space;
	int			i;
	int			j;

	if (!*input)
		boolean = false;
	if (what_case == SPACE)
	{
		*dest = ft_substr(*input, 0, ft_strchr(*input, what_case) - *input);
		*input += ft_strlen(*dest);
	}
	else
	{
		first_quote = ft_strchr(*input, what_case) - *input;
		second_quote = ft_strchr(*input + first_quote + 1, what_case) - *input;
		final_space = ft_strchr(*input + second_quote + 1, SPACE) - *input;
		*dest = malloc(sizeof(char) * (final_space - 1));
		i = -1;
		j = 0;
		while (++i < final_space)
		{
			if (input[0][i] != what_case)
			{
				dest[0][j] = input[0][i];
				j++;
			}
		}
		dest[0][j] = '\0';
		*input += final_space;
	}
}

void	interpret_quotes(char *input, t_cmd_and_opt *cmdopt)
{
	char	what_case;
	bool	boolean;
	int		i;

	cmdopt->option = malloc(sizeof(char *) * ft_strlen(input));
	boolean = true;
	i = 0;
	while (boolean)
	{
		while (*input == SPACE)
			input += 1;
		what_case = which_one(input);
		if (!what_case)
		{
			cmdopt->option[i] = ft_strdup(input);
			i++;
			cmdopt->option[i] = NULL;
			break ;
		}
		words(&input, what_case, &cmdopt->option[i], &boolean);
		i++;
	}
}

