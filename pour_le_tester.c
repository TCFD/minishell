#include "minishell.h"

char	*get_args_simple_into_tab(char **all_args)
{
	char	*tab_out;
	int		idx;
	int		count_all;
	int		count_final;

	idx = 0;
	count_all = 0;
	while (idx < d_len(all_args))
	{
		count_all += ft_strlen(all_args[idx]) + 1;
		idx++ ;
	}
	tab_out = malloc(count_all * sizeof(char));
	if (!tab_out)
		return (NULL);
	idx = 0;
	count_final = 0;
	while (all_args[idx])
	{
		int	a = 0;
		int	len = (int)ft_strlen(all_args[idx]);
		while (a < len)
		{
			tab_out[count_final] = all_args[idx][a];
			count_final++ ;
			a++ ;
		}
		tab_out[count_final] = ' ';
		count_final++ ;
		idx++ ;
	}
	tab_out[count_final] = '\0';
	return (tab_out);
}

void	minishell_tester(char *input, t_cmd_and_opt *cmdopt)
{
	init_cmdopt(cmdopt);
	if (ft_strncmp(input, "exit", 4) == 0)
		return (exit_func(cmdopt, input));
	if (input[0])
	{
		create_command(input, cmdopt);
		add_history(input);
	}
	execute_command(cmdopt);
	if (input[0])
		free_cmdopt(cmdopt);
	free(input);
	return ;
}


void	run_minishell_tester(char **args, t_cmd_and_opt *cmdopt)
{
	char	*join;
	char	*input = get_args_simple_into_tab(args);

	join = NULL;
	shlvl_plus_one(&join);
	minishell_tester(input, cmdopt);
	rl_clear_history();
	shlvl_minus_one();
	free_cmdopt(cmdopt);
	free(join);
}
