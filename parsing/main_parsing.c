/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:35:02 by zbp15             #+#    #+#             */
/*   Updated: 2023/07/04 18:53:44 by zbp15            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Retourne soit "simple quote", "double quote", "space" ou "no quote", suivant ce qu'il y a en premier dans la string.

char which_one(char *input)
{
	char *first_simple_quote;
	char *first_double_quote;
	char *first_space;

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

// Redirige vers la fonction qui va traiter selon les cas

/* void words(char **input, char what_case, char **dest, char *type)
{
	if (what_case == SPACE)
		//redirection vers la fonction qui va traiter les espaces
	else if (what_case == SIMPLE_Q || what_case == DOUBLE_Q)
		//redirection vers la fonction qui va traiter les quotes
	else
		//redirection vers la fonction qui va traiter les la fin de string
} */

//listes chainées

void	parse_that_shit(char *input, t_cmd_and_opt *cmdopt, int i)
{
	char what_case;

	(void)(input);
	(void)(cmdopt);
	(void)(i);
	while (*input == SPACE)
		input += 1;
	cmdopt->opt_and_type_tab.tab = ft_calloc(sizeof(char *), (ft_strlen(input) + 1));
	cmdopt->opt_and_type_tab.type = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (*input)
	{
		printf("%s\n", input);
	}
	cmdopt->opt_and_type_tab.tab[i] = NULL;
}
