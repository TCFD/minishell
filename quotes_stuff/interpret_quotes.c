/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:06:57 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/21 15:19:39 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	which_one(char *input)
{
	char	*first_simple_quote;
	char	*first_double_quote;
	char	*first_space;

	first_simple_quote = ft_strchr_rc(input, '\'');
	first_double_quote = ft_strchr_rc(input, '\"');
	first_space = ft_strchr_rc(input, ' ');
	if (first_simple_quote == NULL)
		first_simple_quote = input + ft_strlen(input);
	if (first_double_quote == NULL)
		first_double_quote = input + ft_strlen(input);
	if (first_space == NULL)
		first_space = input + ft_strlen(input);
	if (first_space < first_double_quote && first_space < first_simple_quote)
		return (SPACE);
	if (first_simple_quote < first_double_quote)
		return (SIMPLE_Q);
	if (first_simple_quote > first_double_quote)
		return (DOUBLE_Q);
	return ('\0');
}

void	qutoes_case(char **input, char what_case, char **dest, int j)
{
	long int		first_quote;
	long int		second_quote;
	long int		final_space;
	int				i;

	first_quote = ft_strchr_rc(*input, what_case) - *input;
	second_quote = ft_strchr_rc(*input + first_quote + 1, what_case) - *input;
	final_space = (long int)ft_strchr_rc(*input + second_quote + 1, SPACE);
	if (final_space == 0)
		final_space = ft_strlen(*input);
	else
		final_space -= (long int)*input;
	*dest = malloc(sizeof(char) * (final_space - 1));
	i = -1;
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

void	words(char **input, char what_case, char **dest, char *type)
{
	if (what_case == SPACE)
	{
		*dest = ft_substr(*input, 0, ft_strchr_rc(*input, what_case) - *input);
		*input += ft_strlen(*dest);
		*type = NONE;
	}
	else
	{
		qutoes_case(input, what_case, dest, 0);
		*type = what_case;
	}
}

void	interpret_quotes(char *input, t_cmd_and_opt *cmdopt)
{
	char	what_case;
	int		i;

	cmdopt->option.opt_tab = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	cmdopt->option.type = malloc(sizeof(char) * (ft_strlen(input)));
	i = 0;
	while (*input == SPACE)
		input += 1;
	while (*input)
	{
		what_case = which_one(input);
		if (!what_case)
		{
			cmdopt->option.opt_tab[i] = ft_strdup(input);
			i++;
			cmdopt->option.opt_tab[i] = NULL;
			cmdopt->option.type[i] = NONE;
			break ;
		}
		words(&input, what_case, &cmdopt->option.opt_tab[i],
			&cmdopt->option.type[i]);
		i++;
		while (*input == SPACE)
			input += 1;
	}
}
