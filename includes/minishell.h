/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:11:36 by wolf              #+#    #+#             */
/*   Updated: 2023/09/24 17:43:36 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define YELLOW				"\033[33m"
# define BLUE				"\033[34m"
# define PURPLE				"\033[35m"
# define WHITE				"\033[37m"

# define RED_1				"\033[31;1m"
# define GREEN_1			"\033[32;1m"
# define YELLOW_1			"\033[33;1m"
# define BLUE_1				"\033[34;1m"
# define PURPLE_1			"\033[35;1m"
# define WHITE_1			"\033[37;1m"

# define ANIM_C				GREEN
# define CD_C				WHITE_1

# define NC					"\033[0m"

# define SIMPLE_Q			'\''
# define DOUBLE_Q			'\"'
# define SPACE				' '
# define NONE				'\0'
# define S_R_RAFTER			">"
# define D_R_RAFTER			">>"
# define S_L_RAFTER			"<"
# define D_L_RAFTER			"<<"
# define PIPE				"|"

# define ANIME_TIME			5000000

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>

# include "libft_stuff/libft.h"
# include "pipex.h"

// GLOBALE //
extern int	g_error_code;
/* 
	
	[---------| struct |---------]

*/
typedef struct s_redirections
{
	t_list	*list;
	int		counter;
	int		stdout_save;
	int		stdin_save;
	int		file_in_fd;
	int		file_out_fd;
	bool	heredoc;
	char	*random_adress;
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
	char	*home_path;
	int		count;
}t_singleton;

typedef struct s_singleton2
{
	char	*l_ety;
	char	*prompt;
	int		env_i;
	int		fix_env_i;
	int		sign_ctrl;
	int		last_sign_ctrl;
	int		last_sign;
}t_singleton2;

typedef struct c_cd
{
	char	*env_pwd;
	char	*env_old_pwd;
	int		env_pwd_true;
	int		env_oldpwd_true;
}t_cd;

typedef struct s_opt_tab
{
	char	**tab;
	char	*type;
}t_opt_tab;

// CMDOPT //
typedef struct s_command_and_option
{
	char			*command_name;
	char			*command_path;
	int				path_unset;
	t_opt_tab		opt_ty_tb;
}t_cmd_and_opt;

// DOLLAR //
typedef struct s_dollar
{
	int		start;
	int		end;
	char	*tmp_dup;
	char	*env_var;
}t_dollar;

t_singleton2	*get_singleton2_instance(void);
t_singleton		*get_singleton_instance(void);
t_list			*all_tokens(char *input, t_list *list, int i, int len);
t_list			*get_tokens(char *input);
/* 
	
	[---------| char ** |---------]

*/
char			**alloc_env(char **env);
char			**list_to_d_tab(t_list *list);
char			**double_a_realloc(char **array, char *new_elmt);
char			**ft_d_strdup(char **tab);
char			**get_env(void);
/* 
	
	[---------| char * |---------]

*/
char			*get_brut_cmd_result(char *cmd);
char			*is_path_unset(char *command_name, int imd_return);
char			*create_path(char *command_name, int imd_return);
char			*get_char_until_limit(char *str, int lim);
char			*check_env_variables(char *input, int end);
char			*d_t_case(char *input, t_list **list, t_dollar *dollar);
char			*replace_dollar(char what_case, char *input,
					int i, t_list **list);
char			*stick_color(char *str, char *color);
char			*build_username_prompt(char *username);
char			*display_user_prompt(char *username);
char			*join_by_value(char *var_name, char *value);
char			*read_bytes(int *fd);
char			*get_execve_return(t_cmd_and_opt *cmdopt);
char			*brut_name(char *command_np);
char			*get_env_var(char *var_name);
char			*ft_getenv(char *var_name);
char			*get_pwd(void);
char			*get_pwd_for_pwd(void);
char			*special_cara_cd(char *cd_arg);
char			*get_opendir_value(t_cmd_and_opt *cmdopt,
					bool is_malloc, DIR *file);
char			*get_pwd_path(void);
char			*get_env_pwd(void);
char			*get_env_oldpwd(void);
char			*get_username(void);
char			*get_home_path(void);
char			*getenv_check(char *str);
char			*build_prompt(int u_len, char *builded_username,
					char *building_result);
char			*get_prompt(void);
char			*get_last_entry(void);
/* 
	
	[---------| char |---------]

*/
char			find_first_isf(char *input);
char			which_one(char *input);
char			search_first_separator(char *input, int len);
/* 

	[---------| void |---------]

*/
void			minishell(char *input, t_cmd_and_opt *cmdopt, char *prompt);
void			run_minishell(void);
void			initialise_home_path(void);
void			redo_path_and_name(t_cmd_and_opt *cmd);
void			remove_in_redirections2(char **tab, char *type,
					t_redirections *redi, int i);
void			restore_stdin(t_redirections *redir);
void			temp_heredoc(char *str, char **random_adress);
void			lst_add(t_list **list, char **content, char type);
void			restore_stdout(int stdout_save, int filefd);
void			init_fork_opt(t_fork_opt *fork_utils);
void			free_fork_opt(t_fork_opt *fork_utils);
void			fork_it(t_fork_opt *fork_utils);
void			execute_pipex(char **lst_cmd);
void			case_1(t_separators *sep, char **content,
					char *input, t_list **list);
void			case_2_or_3(t_separators *sep, char **content, char *input,
					t_list **list);
void			case_4_or_5(t_separators *sep, char **content,
					char *s1, t_list **list);
void			case_4_5_part_2(t_separators *sep, char **content, char *input,
					t_list **list);
void			final_case(t_separators *sep, char **content, char *input,
					t_list **list);
void			parse_that_shit(char *tmp, t_cmd_and_opt *cmdopt);
void			create_command(char	*input, t_cmd_and_opt *cmdopt);
void			init_tabs(char char_tab[6], long int tab[6], char *input);
void			set_separator(t_separators *sep, char *input);
void			stack_cpy(char *tab_stack, char *tab_heap);
void			bf_prd(char *str, int d, char *color);
void			welcome_to_minishell(void);
void			sig_handler(int signum);
void			init_cmdopt(t_cmd_and_opt *cmdopt);
void			free_d_int(int **elmt, int len);
void			free_d_array(char **str);
void			free_t_array(char ***str);
void			free_cmdopt(t_cmd_and_opt *cmdopt);
void			free_everything(t_cmd_and_opt *cmdopt, bool f_cmdopt);
void			update_err_code(int code_err);
void			write_env_oldpwd(char *oldpwd);
void			write_env_pwd(char *pwd);
void			ft_exit(int code);
void			update_err_code_exit(char *origin_code, int code_err);
void			exit_prg(char *code_err);
void			export_var(char *var, bool update_g);
void			export_all_var(t_cmd_and_opt *cmdopt);
void			verif_env_and_path(t_cmd_and_opt *cmdopt);
void			rebuild_env(void);
void			unset_env_var(char *variable);
void			unset_all_env_var(t_cmd_and_opt *cmdopt);
void			display_env(char **env, t_cmd_and_opt *cmdopt);
void			print_pwd(void);
void			cd_remake(t_cmd_and_opt *cmdopt);
void			skip_n(t_cmd_and_opt *cm, int *i, int *j, bool *boolean);
void			echo_remake(t_cmd_and_opt *cm);
void			env_var_plus_one(char *env_var);
void			env_var_minus_one(char *env_var);
void			update_env(char **new_value);
void			update_env_detection(int new_value);
void			free_env_singleton(void);
void			update_sign_ctrl(int value);
void			update_last_sign(int value);
void			update_pwd(char *new_value);
void			update_env_pwd(char *new_value);
void			update_env_oldpwd(char *new_value);
void			update_username(const char *newValue);
void			free_last_value(void);
void			update_home_path(char *new_value);
void			free_str(char **str);
void			one_time_animation_start(void);
void			one_time_animation_end(void);
void			add_cmd_to_history_and_run(int check, t_cmd_and_opt *cmdopt,
					char *input, int i);
void			check_to_add_history(char *input);
void			loop_it(t_cmd_and_opt *cmdopt,
					char *input, int i);
void			update_prompt(char *new_prompt);
void			update_last_entry(char *last_entry);
void			init_prompt_last_entry(void);
void			free_prompt_last_entry(void);
void			change_underscore_value(t_cmd_and_opt *cmdopt, bool update_g);
void			change_underscore_value_void(bool update_g);
void			check_sign_return(int minishell_call);
/* 

	[---------| int |---------]

*/
int				add_rest(char **tab, char *type, int i, t_redirections *redir);
int				open_sub_file(char **tab, int *i, int *funct_counter);
int				remove_redirections(char **tab, char *type,
					t_redirections *redir);
int				search_out_redirections(t_cmd_and_opt *cmdopt,
					t_redirections *redir, bool *redir_bool);
int				search_if_file_exist(char *filename);
int				redirect_input(char **tab, int *stdin_save, int *filefd,
					char **random_adress);
int				add_rest_in(char **tab, char *type,
					int i, t_redirections *redir);
int				remove_in_redirections(char **tab, char *type,
					t_redirections *redi, int i);
int				count_in_redirs(char **tab, char *type, bool *heredoc);
int				search_in_redirections(t_cmd_and_opt *cmdopt,
					t_redirections *redir, bool *redir_bool);
int				redirect_output(char **tab, int *stdout_save,
					int *filefd, int which_case);
int				count_out_redirs(char **tab, char *type);
int				get_func(t_fork_opt *fork_utils);
int				get_marker_value(t_fork_opt *fork_utils);
int				find_command_pipex(t_cmd_and_opt *cmdopt);
int				check_input(char *input);
int				check_correct_quotes(char *input);
int				what_case_equal_c(char c, char c2);
int				does_command_path_valid(char *cmd);
int				check_valid_file_name(char **t, char *type);
int				heck_if_same(char *s1, char *s2);
int				find_first_occurence(char *str, char cara);
int				check_if_ifs(char c);
int				find_first_non_valid(char *input, int i);
int				get_word_index(char *str, char const *word);
int				d_len(char **str);
int				t_len(char ***str);
int				run_execve(t_cmd_and_opt *cmdopt);
int				cmp(char *cmd_name, char *cmd_name_2);
int				find_command(t_cmd_and_opt *cmdopt);
int				execute_command(t_cmd_and_opt *cmdopt);
int				export_name_unvalid(char *var);
int				verif_if_env_called(t_cmd_and_opt *cmdopt);
int				ft_getenv_int(char *var_name);
int				get_env_detection(void);
int				get_sign_ctrl(void);
int				get_last_sign(void);
int				get_fix_env_detection(void);
int				man_minishell(t_cmd_and_opt *cmdopt);
int				exit_func(t_cmd_and_opt *cmdopt, char *input);
int				verif_signal(int status, char *cmd_name);
int				go_to_cmd(t_cmd_and_opt *cmdopt);
int				minishell_with_arg(t_cmd_and_opt *cmdopt);
int				check_if_input_minishell(t_cmd_and_opt *cmdopt,
					char *input);
int				cmd_exist(t_cmd_and_opt *cmdopt);
/* 

	[---------| bool |---------]

*/
bool			is_there_a_command(t_opt_tab opt);

#endif