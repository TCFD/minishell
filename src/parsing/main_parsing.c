/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:35:02 by zbp15             #+#    #+#             */
/*   Updated: 2023/09/29 17:58:49 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	switch_func(t_separators *sep, char **content, char *input, t_list **list)
{
	if (sep->s_string < sep->w_string)
	{
		if (!case_1(sep, content, input, list))
			return (0);
	}
	else
	{
		if (sep->what_case == SIMPLE_Q || sep->what_case == DOUBLE_Q)
		{
			if (!case_2_or_3(sep, content, input, list))
				return (0);
		}
		else
		{
			if (!final_case(sep, content, input, list))
				return (0);
		}
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
		if (!switch_func(&sep, &content, input, &list))
			return (0);
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
		return (free(input), malloc_failure(), NULL);
	tmp = list;
	i = 0;
	while (input[i] == SPACE)
		i += 1;
	if (!all_tokens(input, tmp, i, ft_strlen(input)))
		return (ft_lstclear(&list), free(input), malloc_failure(), NULL);
	return (list);
}

void	free_backwards(char **tab, int i)
{
	while (--i >= 0)
		free(tab[i]);
	free(tab);
}

void	parse_that_shit(char *tmp, t_cmd_and_opt *cmdopt)
{
	t_list	*list;
	t_list	*temp_list;
	char	*input;
	int		i;

	input = ft_strdup(tmp);
	if (!input)
		malloc_failure();
	list = get_tokens(input);
	temp_list = list;
	cmdopt->opt_ty_tb.tab = ft_calloc(ft_lstsize(list), sizeof(char *));
	if (!cmdopt->opt_ty_tb.tab)
		return (ft_lstclear(&list), malloc_failure());
	cmdopt->opt_ty_tb.type = ft_calloc(ft_lstsize(list), sizeof(char));
	if (!cmdopt->opt_ty_tb.type)
		return (ft_lstclear(&list), malloc_failure());
	i = 0;
	while (temp_list->next)
	{
		cmdopt->opt_ty_tb.tab[i] = ft_strdup(temp_list->content);
		if (!cmdopt->opt_ty_tb.tab[i])
			return (free(cmdopt->opt_ty_tb.type), malloc_failure());
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
		return ((void)(ft_printf(2, "Minishell : incorect quotes.\n")));
	parse_that_shit(input, cmdopt);
	if (check_valid_file_name(cmdopt->opt_ty_tb.tab, cmdopt->opt_ty_tb.type))
		return (update_err_code(2));
	if (get_env_detection() == 1)
	{
		if (!ft_getenv("PATH"))
		{
			cmdopt->command_name = create_path
				(ft_strdup(cmdopt->opt_ty_tb.tab[0]), 0);
			cmdopt->command_path = ft_cpy(cmdopt->command_name, 0);
			return ;
		}
		update_env_detection(0);
	}
	cmdopt->command_name = ft_strdup(cmdopt->opt_ty_tb.tab[0]);
	if (cmdopt->command_name[0])
		cmdopt->command_path = create_path
			(ft_strdup(cmdopt->opt_ty_tb.tab[0]), 1);
	else
		cmdopt->command_path = NULL;
}
