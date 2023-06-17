/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:11:15 by wolf              #+#    #+#             */
/*   Updated: 2023/06/17 16:30:47 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PURPLE	"\033[35m"
# define NC		"\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "INCLUDES/libft.h"
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_command_and_option
{
	char	*command_name;
	char	*command_path;
	char	**option;
}t_cmd_and_opt;

char	**create_options(char *cmd_name, char **all_args);
char	*getenv_check(char *str);
char	*display_user_prompt(void);
char	*ccn(char *str, char *color);
char	*stick_color(char *str, char *color);
char	*create_path(char *command_name);
char	*brut_name(char *command_np);
void	create_command(char	*input, t_cmd_and_opt *cmdopt);
void	sigint_handler();
void	free_d_array(char **str);
void	free_t_array(char ***str);
void	free_cmdopt(t_cmd_and_opt *cmdopt);
void	init_cmdopt(t_cmd_and_opt *cmdopt);
void	run_execve(t_cmd_and_opt *cmdopt);
void	execute_command(t_cmd_and_opt *cmdopt);
int		d_len(char **str);
int		t_len(char ***str);

#endif
