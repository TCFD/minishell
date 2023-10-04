/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:35:02 by zbp15             #+#    #+#             */
/*   Updated: 2023/10/04 16:36:42 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	switch_func(t_separators *sep, char **content, char *input, t_list **list)
{
	if (sep->s_string < sep->w_string)
		case_1(sep, content, input, list);
	else
	{
		if (sep->what_case == SIMPLE_Q || sep->what_case == DOUBLE_Q)
			case_2_or_3(sep, content, input, list);
		else
			final_case(sep, content, input, list);
	}
	return (1);
}

int	all_tokens(char *input, t_list *list, int i, int len)
{
	char			*content;
	t_separators	sep;

	sep.i = i;
	while (sep.i < len)
	{
		set_separator(&sep, input);
		switch_func(&sep, &content, input, &list);
		while (check_if_ifs(input[sep.i]) && input[sep.i])
			sep.i += 1;
	}
	list = NULL;
	return (1);
}

t_list	*get_tokens(char *input)
{
	t_list	*list;
	t_list	*tmp;
	int		i;

	list = ft_lstnew("", '\0');
	if (!list)
		return (malloc_failure(), NULL);
	tmp = list;
	i = 0;
	while (input[i] && check_if_ifs(input[i]))
		i += 1;
	if (!all_tokens(input, tmp, i, ft_strlen(input)))
		return (malloc_failure(), NULL);
	return (list);
}

void	parse_that_shit(char *tmp, t_cmd_and_opt *cmdopt)
{
	t_list	*list;
	t_list	*temp_list;
	char	*input;

	input = ft_strdup(tmp);
	if (!input)
		malloc_failure();
	list = get_tokens(input);
	temp_list = list;
	cmdopt->opt_ty_tb.tab = ft_calloc(ft_lstsize(list), sizeof(char *));
	if (!cmdopt->opt_ty_tb.tab)
		return (malloc_failure());
	//garbage_add((void *)cmdopt->opt_ty_tb.tab);
	cmdopt->opt_ty_tb.type = ft_calloc(ft_lstsize(list), sizeof(char));
	if (!cmdopt->opt_ty_tb.type)
		return (malloc_failure());
	//garbage_add((void *)cmdopt->opt_ty_tb.type);
	fill_cmdopt(cmdopt, temp_list);
}

void	create_command(char	*input, t_cmd_and_opt *cmdopt)
{
	if (!input || !input[0])
		return ;
	if (!check_correct_quotes(input))
		return ((void)(ft_printf(2, "Minishell : incorect quotes.\n")));
	parse_that_shit(input, cmdopt);
	if (get_env_detection() == 1)
	{
		if (!ft_getenv("PATH"))
		{
			cmdopt->command_name = create_path
				(cmdopt->opt_ty_tb.tab[0], 0);
			cmdopt->command_path = ft_cpy(cmdopt->command_name, 0);
			return ;
		}
		update_env_detection(0);
	}
	cmdopt->command_name = ft_strdup(cmdopt->opt_ty_tb.tab[0]);
	if (!cmdopt->command_name)
		return (malloc_failure());
	if (cmdopt->command_name[0])
		cmdopt->command_path = create_path
			(cmdopt->opt_ty_tb.tab[0], 1);
	else
		cmdopt->command_path = NULL;
}
