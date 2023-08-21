/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:35:02 by zbp15             #+#    #+#             */
/*   Updated: 2023/08/21 19:08:37 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*all_tokens(char *input, t_list *list, int i, int len)
{
	char			*content;
	t_separators	sep;

	sep.i = i;
	while (sep.i < len)
	{
		set_separator(&sep, input);
		if (sep.s_string < sep.w_string)
			case_1(&sep, &content, input, &list);
		else
		{
			if (sep.what_case == SIMPLE_Q || sep.what_case == DOUBLE_Q)
				case_2_or_3(&sep, &content, input, &list);
			else
				final_case(&sep, &content, input, &list);
		}
		while (check_if_IFS(input[sep.i]) && input[sep.i])
			sep.i += 1;
	}
	list = NULL;
	return (list);
}

t_list	*get_tokens(char *input)
{
	t_list	*list;
	t_list	*tmp;
	int		i;

	list = ft_lstnew("", '\0');
	tmp = list;
	i = 0;
	while (input[i] == SPACE)
		i += 1;
	all_tokens(input, tmp, i, ft_strlen(input));
	return (list);
}

void	parse_that_shit(char *tmp, t_cmd_and_opt *cmdopt)
{
	t_list	*list;
	t_list	*temp_list;
	char	*input;
	int		i;

	input = ft_strdup(tmp);
	list = get_tokens(input);
	temp_list = list;
	cmdopt->opt_ty_tb.tab = ft_calloc(ft_lstsize(list), sizeof(char *));
	cmdopt->opt_ty_tb.type = ft_calloc(ft_lstsize(list), sizeof(char));
	i = 0;
	while (temp_list->next)
	{
		cmdopt->opt_ty_tb.tab[i] = ft_strdup(temp_list->content);
		cmdopt->opt_ty_tb.type[i] = temp_list->type;
		temp_list = temp_list->next;
		i++;
	}
	cmdopt->opt_ty_tb.tab[i] = NULL;
	cmdopt->opt_ty_tb.type[i] = '\0';
	ft_lstclear(&list);
	free(input);
}

void	create_command(char	*input, t_cmd_and_opt *cmdopt)
{
	if (!input[0])
		return ;
	if (!check_correct_quotes(input))
		return ((void)(printf("Minishell : incorect quotes.\n")));
	parse_that_shit(input, cmdopt);
	if (check_valid_file_name(cmdopt->opt_ty_tb.tab, cmdopt->opt_ty_tb.type))
		return ;
	if (cmdopt->path_unset == 0 && !ft_getenv("PATH"))
	{
		cmdopt->command_name = create_path
			(ft_strdup(cmdopt->opt_ty_tb.tab[0]), 0);
		cmdopt->command_path = ft_cpy(cmdopt->command_name, 0);
	}
	else
	{
		cmdopt->command_name = ft_strdup(cmdopt->opt_ty_tb.tab[0]);
		cmdopt->command_path = create_path
			(ft_strdup(cmdopt->opt_ty_tb.tab[0]), 1);
	}
}
