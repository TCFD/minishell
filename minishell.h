/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:11:15 by wolf              #+#    #+#             */
/*   Updated: 2023/07/05 19:18:33 by tboldrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define YELLOW				"\033[33m"
# define BLUE				"\033[34m"
# define PURPLE				"\033[35m"
# define NC					"\033[0m"
# define SIMPLE_Q			'\''
# define DOUBLE_Q			'\"'
# define SPACE				' '
# define NONE				'\0'
# define INTERPRETABLE		'y'
# define NOT_INTERPRETABLE	'n'

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "INCLUDES/libft.h"
# include "pipe_and_redirections/pipe/pipex/pipex_bonus.h"
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
extern int	error_code;

typedef struct s_singleton
{
	char	*username;
	char	**env;
	int		count;
}t_singleton;

typedef	struct s_opt_tab
{
	char	**tab;
	char	*type;
}t_opt_tab;


typedef struct s_command_and_option
{
	char			*command_name;
	char			*command_path;
	int				path_unset;
	t_opt_tab		opt_ty_tb;
}t_cmd_and_opt;

char		**create_options(char *cmd_name, char **all_args);
char		**double_a_realloc(char **array, char *new_elmt);
char		*getenv_check(char *str);
char		*display_user_prompt(char *username);
char		*stick_color(char *str, char *color);
char		*create_path(char *command_name, int imd_return);
char		*brut_name(char *command_np);
char		*is_path_unset(char *command_name, int imd_return);
void		create_command(char	*input, t_cmd_and_opt *cmdopt);
void		welcome_to_minishell(void);
void		sigint_handler(int signum);
void		cd_remake(t_cmd_and_opt *cmdopt);
void		free_d_array(char **str);
void		free_t_array(char ***str);
void		free_cmdopt(t_cmd_and_opt *cmdopt);
void		init_cmdopt(t_cmd_and_opt *cmdopt);
void		init_design_pattern(t_singleton *design_p);
void		run_execve(t_cmd_and_opt *cmdopt);
void		execute_command(t_cmd_and_opt *cmdopt);
void		bf_prd(char *str, int d, char *color);
void		unset_env_var(char *variable, char **env);
void		unset_all_env_var(t_cmd_and_opt *cmdopt);
void		display_env(char **env, t_cmd_and_opt *cmdopt);
int			check_if_same(char *s1, char *s2);
int			d_len(char **str);
int			t_len(char ***str);
int			use_pipex(char *command);
int			check_correct_quotes(char *input);
void		interpret_quotes(char *input, t_cmd_and_opt *cmdopt, int i);
void		echo_remake(t_cmd_and_opt *cmdopt);
char		*check_env_variables(char *input);
void		expand(char **dest);
int			space_end_case(char **input, char **dest, char what_case, char *type);
int			cmp(char *cmd_name, char *cmd_name_2);
char		*read_bytes(int *fd);
char		*get_execve_return(t_cmd_and_opt *cmdopt);
t_singleton	*get_singleton_instance(void);
void		update_username(const char *newValue);
void		free_last_value(void);
const char	*get_username(void);
int			search_d_tab(t_cmd_and_opt *cmdopt, char *c);
int			redirect_output(char **tab, int *stdout_save, int *filefd,
				int which_case);
void		restore_fd(int position, int stdout_save, int filefd);
int			search_redirections(t_cmd_and_opt *cmdopt, int *stdout_save,
				int *filefd, long int *position);
char	*find_chevrons(char **input, int end);

void	shlvl_plus_one(char **join_it);
void	shlvl_minus_one(void);
void	rebuild_env(void);

void	verif_env_and_path(t_cmd_and_opt *cmdopt);

t_singleton	*get_env_instance(void);
void		update_env(char **new_value);
char		**get_env(void);


char	*ft_getenv(char *var_name);
int		ft_getenv_int(char *var_name);
void	export_var(char *var);
void	export_all_var(t_cmd_and_opt *cmdopt);

char	**ft_d_strdup(char **tab);
char	*get_char_until_limit(char *str, int lim);
int		find_first_occurence(char *str, char cara);

int		does_command_path_valid(char *cmd);
int		verif_if_env_called(t_cmd_and_opt *cmdopt);

void	update_err_code(int code_err);
void	update_err_code_exit(int code_err);
void	ft_exit(char *code_err);
void	update_err_code_exit(int code_err);


char	*get_pwd(void);
void	print_pwd(void);

void	exit_func(t_cmd_and_opt *cmdopt, char *input);
int		get_word_index(char const *str, char const *word);

// ------- Pour le tester --------//

char	*get_args_simple_into_tab(char **all_args);
void	minishell_tester(char *input, t_cmd_and_opt *cmdopt);
void	run_minishell_tester(char **args, t_cmd_and_opt *cmdopt);

// ------------------------------//

#endif
