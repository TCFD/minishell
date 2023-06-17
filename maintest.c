/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:45:37 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 15:54:28 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ----
char	*getenv_check(char *str)
{
	char	*found_it;

	found_it = getenv(str);
	if (found_it == NULL)
		return (NULL);
	return (found_it);
}

void	print_options(t_cmd_and_opt *cmdopt)
{
	int	idx;

	idx = 0;
	if (!cmdopt->option)
	{
		ft_printf("\n");
		return ;
	}
	while (cmdopt->option[idx])
	{
		ft_printf("\"%s\" ", cmdopt->option[idx]);
		idx++ ;
	}
	ft_printf("\n");
}

int	main(void)
{
	t_cmd_and_opt	cmdopt;
	char			*prompt;
	char			*input;

	signal(SIGINT, sigint_handler);
	prompt = display_user_prompt();
	while ((input = readline(prompt)) != NULL && ft_strncmp(input, "exit", 4) != 0)
	{
		init_cmdopt(&cmdopt);
		if (input[0])
		{
			create_command(input, &cmdopt);
			ft_printf("command name : %s\n", cmdopt.command_name);
			ft_printf("options      : ");
			print_options(&cmdopt);
			add_history(input);
		}
		free(input);
		free_cmdopt(&cmdopt);
	}
	free(prompt);
	return (0);
}
