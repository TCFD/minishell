/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:11:15 by wolf              #+#    #+#             */
/*   Updated: 2023/06/27 16:33:26 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define NC			"\033[0m"
# define SIMPLE_Q	'\''
# define DOUBLE_Q	'\"'
# define SPACE		' '
# define NONE		'\0'

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "INCLUDES/libft.h"
# include "pipe_stuff/pipex/pipex_bonus.h"
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_singleton
{
	char	*last_value;
}t_singleton;

typedef struct s_command_and_option
{
	char			*command_name;
	char			*command_path;
	char			**opt_tab;
}t_cmd_and_opt;

extern char **environ; // Variable Globale

char		**create_options(char *cmd_name, char **all_args);
char		**double_a_realloc(char **array, char *new_elmt);
char		*getenv_check(char *str);
char		*display_user_prompt(char *username);
char		*stick_color(char *str, char *color);
char		*create_path(char *command_name);
char		*brut_name(char *command_np);
char		*is_path_unset(char *command_name);
void		create_command(char	*input, t_cmd_and_opt *cmdopt);
void		welcome_to_minishell(void);
void		sigint_handler(int signum);
void		cd_remake(t_cmd_and_opt *cmdopt);
void		free_d_array(char **str);
void		free_t_array(char ***str);
void		free_cmdopt(t_cmd_and_opt *cmdopt);
void		init_cmdopt(t_cmd_and_opt *cmdopt);
void		run_execve(t_cmd_and_opt *cmdopt);
void		execute_command(t_cmd_and_opt *cmdopt);
void		bf_prd(char *str, int d, char *color);
void		unset_env_var(char *variable);
void		unset_all_env_var(t_cmd_and_opt *cmdopt);
void		display_env(void);
int			check_if_same(char *s1, char *s2);
int			d_len(char **str);
int			t_len(char ***str);
int			use_pipex(char *command);
int			check_correct_quotes(char *input);
void		interpret_quotes(char *input, t_cmd_and_opt *cmdopt);
void		echo_remake(t_cmd_and_opt *cmdopt);
char		*check_env_variables(char *input);
void		expand(char **dest);
int			space_end_case(char **input, char **dest, char what_case);
int			cmp(char *cmd_name, char *cmd_name_2);
char		*read_bytes(int *fd);
char		*get_execve_return(t_cmd_and_opt *cmdopt);
t_singleton	*get_singleton_instance(void);
void		update_username(const char *newValue);
void		free_last_value(void);
const char	*get_username(void);

#endif
