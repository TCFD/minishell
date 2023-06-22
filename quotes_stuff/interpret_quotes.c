/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:06:57 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/22 17:51:53 by rciaze           ###   ########.fr       */
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

long int	assign_values(long int *f_quote, long int *s_quote,
	char what_case, char **input)
{
	long int		final_space;

	final_space = 0;
	*f_quote = ft_strchr_rc(*input, what_case) - *input;
	*s_quote = ft_strchr_rc(*input + *f_quote, what_case) - *input;
	if (*input + *s_quote)
		final_space = (long int)ft_strchr_rc(*input + *s_quote + 1, SPACE);
	else
		final_space = ft_strlen(*input);
	if (final_space == 0)
		final_space = ft_strlen(*input);
	else
		final_space -= (long int)*input;
	return (final_space);
}

void	qutoes_case(char **input, char what_case, char **dest, int j)
{
	long int		first_quote;
	long int		second_quote;
	long int		final_space;
	int				i;

	final_space = assign_values(&first_quote, &second_quote, what_case, input);
	*dest = malloc(sizeof(char) * (final_space));
	if (!*dest)
	{
		perror("malloc fail");
		exit(0);
	}
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
			cmdopt->option.type[i] = NONE;
			i++;
			break ;
		}
		words(&input, what_case, &cmdopt->option.opt_tab[i],
			&cmdopt->option.type[i]);
		i++;
		while (*input == SPACE)
			input += 1;
	}
	cmdopt->option.opt_tab[i] = NULL;
}
