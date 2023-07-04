/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:06:57 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/04 16:09:26 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// space_end_case is in minishell/utils/dollar_completion.c

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

long int	assign_values(long int *f_quote, long int *s_quote,
	char what_case, char **input)
{
	long int		final_space;

	final_space = 0;
	*f_quote = ft_strchr_rc(*input, what_case) - *input;
	*s_quote = ft_strchr_rc(*input + *f_quote + 1, what_case) - *input;
	if (*input + *s_quote > *input)
		final_space = ft_strchr_rc(*input + *s_quote + 1, SPACE) - *input;
	if (final_space <= 0)
		final_space = ft_strlen(*input);
	return (final_space);
}

int	qutoes_case(char **input, char what_case, char **dest, char *type)
{
	long int		first_quote;
	long int		second_quote;
	long int		final_space;
	int				i;
	int				j;

	j = 0;
	final_space = assign_values(&first_quote, &second_quote, what_case, input);
	*dest = ft_calloc(sizeof(char), final_space + 1);
	if (!*dest)
		return (perror("malloc fail"), exit(0), 0);
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
	if (what_case == DOUBLE_Q && ft_strchr(*dest, '$'))
		expand(dest);
	*type = NOT_INTERPRETABLE;
	return (i);
}

void	words(char **input, char what_case, char **dest, char *type)
{
	if (what_case == SPACE)
		*input += space_end_case(input, dest, SPACE, type);
	else
		*input += qutoes_case(input, what_case, dest, type);
}

void	interpret_quotes(char *input, t_cmd_and_opt *cmdopt, int i)
{
	char	what_case;

	while (*input == SPACE)
		input += 1;
	cmdopt->opt_ty_tb.tab = ft_calloc(sizeof(char *), (ft_strlen(input) + 1));
	cmdopt->opt_ty_tb.type = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (*input)
	{
		what_case = which_one(input);
		if (!what_case)
		{
			input += space_end_case(&input, &cmdopt->opt_ty_tb.tab[i], NONE, &cmdopt->opt_ty_tb.type[i]);
			i++;
			what_case = which_one(input);
			if (!what_case)
				break ;
			while (*input == SPACE)
				input += 1;
		}
		words(&input, what_case, &cmdopt->opt_ty_tb.tab[i], &cmdopt->opt_ty_tb.type[i]);
		i++;
		while (*input == SPACE)
			input += 1;
	}
	cmdopt->opt_ty_tb.tab[i] = NULL;
}
