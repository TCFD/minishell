/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:11:15 by wolf              #+#    #+#             */
/*   Updated: 2023/08/21 19:06:51 by rciaze           ###   ########.fr       */
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
# define S_R_RAFTER	">"
# define D_R_RAFTER	">>"
# define S_L_RAFTER	"<"
# define D_L_RAFTER	"<<"
# define PIPE				"|"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "INCLUDES/libft.h"
# include "pipe_and_redirections/pipe/pipex_for_minishell/pfm.h"
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
extern int	error_code;

typedef struct s_redirections
{
	t_list	*list;
	int		counter;
	int		stdout_save;
	int		stdin_save;
	int		file_in_fd;
	int		file_out_fd;
	bool	heredoc;
}t_redirections;

typedef struct s_separators
{
	char		what_case;
	char		separator;
	bool		double_sep;
	long int	w_string;
	long int	s_string;
	char		tmp;
	int			i;
	int			tmp_i;
}t_separators;

typedef struct s_singleton
{
	char	*username;
	char	**env;
	char	*pwd;
	char	*env_pwd;
	char	*env_oldpwd;
	int		count;
	int		sign_ctrl;
}t_singleton;

typedef struct c_cd
{
	char	*env_pwd;
	char	*env_old_pwd;
	int		env_pwd_true;
	int		env_oldpwd_true;
} t_cd;

typedef	struct s_opt_tab
{
	char	**tab;
	char	*type;
}t_opt_tab;

// S : COMMAND AND OPTION
typedef struct s_command_and_option
{
	char			*command_name;
	char			*command_path;
	int				path_unset;
	t_opt_tab		opt_ty_tb;
}t_cmd_and_opt;

// S : DOLLAR
typedef struct s_dollar
{
	int		start;
	int		end;
	char	*tmp_dup;
	char 	*env_var;
}t_dollar;


char		**double_a_realloc(char **array, char *new_elmt);
char		*getenv_check(char *str);
char		*display_user_prompt(char *username);
char		*stick_color(char *str, char *color);
char		*create_path(char *command_name, int imd_return);
char		*is_path_unset(char *command_name, int imd_return);
void		create_command(char	*input, t_cmd_and_opt *cmdopt);
void		welcome_to_minishell(void);
void		sig_handler(int signum);
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
void		parse_that_shit(char *input, t_cmd_and_opt *cmdopt);
void		echo_remake(t_cmd_and_opt *cmdopt);
char		*check_env_variables(char *input, int end);
void		expand(char **dest, int start, int if_case);
int			space_end_case(char **input, char **dest, char what_case,
				char *type);
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
void		restore_stdout(int stdout_save, int filefd);
int			search_out_redirections(t_cmd_and_opt *cmdopt,
				t_redirections *redir, bool *redir_bool);
char		*find_chevrons(char **input, int end);
void		shlvl_plus_one(char **join_it);
void		shlvl_minus_one(void);
void		rebuild_env(void);
void		verif_env_and_path(t_cmd_and_opt *cmdopt);
t_singleton	*get_env_instance(void);
void		free_singleton(void);
void		update_env(char **new_value);
char		**get_env(void);
char		*ft_getenv(char *var_name);
int			ft_getenv_int(char *var_name);
void		export_var(char *var);
void		export_all_var(t_cmd_and_opt *cmdopt);

char		**ft_d_strdup(char **tab);
char		*get_char_until_limit(char *str, int lim);
int			find_first_occurence(char *str, char cara);

int			does_command_path_valid(char *cmd);
int			verif_if_env_called(t_cmd_and_opt *cmdopt);

void		update_err_code(int code_err);
void		ft_exit(char *code_err);
char		*get_pwd(void);
void		print_pwd(void);

void		exit_func(t_cmd_and_opt *cmdopt, char *input);
int			get_word_index(char const *str, char const *word);
char		**list_to_d_tab(t_list *list);
int			count_out_redirs(char **tab, char *type);
int			count_in_redirs(char **tab, char *type, bool *heredoc);
void		restore_stdin(t_redirections *redir);
int			search_in_redirections(t_cmd_and_opt *cmdopt,
				t_redirections *redir, bool *redir_bool);
int			redirect_input(char **tab, int *stdin_save, int *filefd);
char		*replace_dollar(char what_case, char *input, int i, t_list **list);
void		case_1(t_separators *sep, char **content, char *input,
				t_list **list);
void		case_2_or_3(t_separators *sep, char **content, char *input,
				t_list **list);
void		case_4_or_5(t_separators *sep, char **content, char *input, t_list **list);
void		case_4_5_part_2(t_separators *sep, char **content, char *input, t_list **list);
void		final_case(t_separators *sep, char **content, char *input,
				t_list **list);
int			check_valid_file_name(char **tab, char *type);
void		set_separator(t_separators *sep, char *input);
t_list		*all_tokens(char *input, t_list *list, int i, int len);
void		lst_add(t_list **list, char **content, char type);
void		temp_heredoc(char *str);
void		redo_path_and_name(t_cmd_and_opt *cmd);
void		update_err_code_exit(char *origin_code, int code_err);


char	*get_pwd(void);
char	*get_pwd_for_pwd(void);
void	print_pwd(void);

void	exit_func(t_cmd_and_opt *cmdopt, char *input);
int		get_word_index(char const *str, char const *word);
void	free_d_int(int **elmt, int len);
int		check_if_IFS(char c);
t_singleton	*get_pwd_instance(void);
char	*get_env_var(char *var_name);
void	update_pwd(char *new_value);
char	*get_pwd_path(void);

void		find_command(t_cmd_and_opt *cmdopt);

void	update_sign_ctrl(int value);
int		get_sign_ctrl(void);

void	stack_cpy(char *tab_stack, char *tab_heap);
void	update_env_pwd(char *new_value);
void	update_env_oldpwd(char *new_value);
char	*get_env_pwd(void);
char	*get_env_oldpwd(void);

void	free_env_singleton(void);

// ------- Pour le tester --------//

char		*get_args_simple_into_tab(char **all_args);
void		minishell_tester(char *input, t_cmd_and_opt *cmdopt);
void		run_minishell_tester(char **args, t_cmd_and_opt *cmdopt);

// ------------------------------//

#endif
