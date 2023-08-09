/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfm1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:53:51 by wolf              #+#    #+#             */
/*   Updated: 2023/08/08 19:22:01 by wolf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


void	free_all_pipes(int	**pipes, int nb_pipes)
{
	int	idx;

	idx = 0;
	while (idx < nb_pipes)
	{
		free(pipes[idx]);
		idx++ ;
	}
	free(pipes);
}


// CREATE PIPES
int	**create_pipes(int number_of_elmt)
{
	int		**pipes;
	int		idx;

	pipes = malloc((number_of_elmt) * sizeof(int *));
	if (!pipes)
		return (0);
	idx = 0;
	while (idx < number_of_elmt)
	{
		pipes[idx] = malloc(2 * sizeof(int));
		if (!pipes[idx])
			return (0);
		if (pipe(pipes[idx]) < 0)
		{
			free(pipes[idx]);
			free(pipes);
			return (0);
		}
		idx++ ;
	}
	return (pipes);
}

// CREATE PIDS
int	*create_pids(int number_of_elmt)
{
	int	*pid;
	int	idx;

	pid = malloc(number_of_elmt * sizeof(int));
	if (!pid)
		return (0);
	idx = 0;
	while (idx < number_of_elmt)
	{
		pid[idx] = 0;
		idx++ ;
	}
	return (pid);
}

// CLOSE ALL DIFF PIPES
void	close_all_diff_pipes(t_pipes *pipes)
{
	int	idx;

	idx = 0;
	while (idx < pipes->idx)
	{
		if (idx == pipes->idx - 1)
		{
			close(pipes->pipes[idx][1]);
			dup2(pipes->pipes[idx][0], STDIN_FILENO);
			close(pipes->pipes[idx][0]);
			
			if (pipes->idx < pipes->len_max - 1)
			{
				close(pipes->pipes[idx + 1][0]);
				dup2(pipes->pipes[idx + 1][1], STDOUT_FILENO);
				close(pipes->pipes[idx + 1][1]);
			}
			return ;
		}
		close(pipes->pipes[idx][0]);
		close(pipes->pipes[idx][1]);
		idx++ ;
	}
}

// PIPES WRITING
void	pipes_writing(t_pipes *pipes)
{
	if (pipes->idx == 0)
	{
		close(pipes->pipes[0][0]);
		dup2(pipes->pipes[0][1], STDOUT_FILENO);
		close(pipes->pipes[0][1]);
	}
	else
		close_all_diff_pipes(pipes);
}

// CLOSE ALL PIPES
void	close_all_pipes(t_pipes *pipes)
{
	int	idx;

	idx = 0;
	while (idx < pipes->idx)
	{
		close(pipes->pipes[idx][0]);
		close(pipes->pipes[idx][1]);
		idx++ ;
	}
}

// WAIT CHILD PROCESS
void	wait_child_process(t_pipes *pipes)
{
	int	idx;
	int	status;

	idx = 0;
	while (idx < pipes->idx + 1)
	{
		waitpid(pipes->pids[idx], &status, 0);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		update_err_code((int)errno);
		idx++ ;
	}
	free(pipes->pids);
}

// EXEC
void	exec(t_cmd_and_opt *cmdopt)
{
	char	*error_join;
	
	if (execve(cmdopt->command_path, cmdopt->opt_ty_tb.tab, get_env()) == -1)
	{
		error_join = ft_join(ft_strdup("bash : "), ft_strdup(cmdopt->command_name));
		perror(error_join);
		free(error_join);
		exit(errno);
	}
}

// EXECUTE PIPE COMMAND
void	execute_pipe_command(t_cmd_and_opt *cmdopt)
{
	long int	position;
	int			stdout_save;
	int			filefd;

	if (!cmdopt->command_name)
		return ;
	search_redirections(cmdopt, &stdout_save, &filefd, &position);
	if (cmp(cmdopt->command_name, "cd"))
		cd_remake(cmdopt);
	else if (cmp(cmdopt->command_name, "unset"))
		unset_all_env_var(cmdopt);
	else if (verif_if_env_called(cmdopt) && !cmdopt->opt_ty_tb.tab[1])
		display_env(get_env(), cmdopt);
	else if (cmp(cmdopt->command_name, "export"))
		export_all_var(cmdopt);
	else if (cmp(cmdopt->command_name, "pwd"))
		print_pwd();
	else
		exec(cmdopt);
	restore_fd(position, stdout_save, filefd);
}

// EXECUTE ALL
void	execute_all(char **elmt)
{
	t_cmd_and_opt	cmdopt;
	t_pipes			pipes;
	int				len_elmt;
	int				idx;

	len_elmt = d_len(elmt);
	pipes.len_max = len_elmt;
	pipes.pipes = create_pipes(len_elmt - 1);
	pipes.pids = create_pids(len_elmt);
	idx = 0;
	while (idx < len_elmt)
	{
		pipes.idx = idx;
		pipes.pids[idx] = fork();
		if (pipes.pids[idx] < 0)
			return ;
		if (pipes.pids[idx] == 0)
		{
			init_cmdopt(&cmdopt);
			pipes_writing(&pipes);
			create_command(elmt[idx], &cmdopt);
			execute_pipe_command(&cmdopt);
			free_cmdopt(&cmdopt);
		} // Func +25
		idx++ ;
	}
	close_all_pipes(&pipes);
	wait_child_process(&pipes);
	free_all_pipes(pipes.pipes, len_elmt - 1);
}

// BRUT TEST ---------
void	brut_test(char **elmt)
{
	t_cmd_and_opt	cmdopt;
	int				pipes1[2], pipes2[2];
	int				pids1, pids2, pids3;
	int				idx;

	idx = 0;
	if (pipe(pipes1) < 0)
		return ;
	pids1 = fork();
	if (pids1 < 0)
		return ;
	if (pids1 == 0)
	{
		close(pipes1[0]);
		dup2(pipes1[1], STDOUT_FILENO);
		close(pipes1[1]);	
		create_command(elmt[idx], &cmdopt);
		exec(&cmdopt);
	}
	if (pipe(pipes2) < 0)
		return ;
	idx = 1;
	pids2 = fork();
	if (pids2 < 0)
		return ;
	if (pids2 == 0)
	{
		close(pipes1[1]);
		close(pipes2[0]);	
		
		dup2(pipes1[0], STDIN_FILENO);
		close(pipes1[0]);
		
		dup2(pipes2[1], STDOUT_FILENO);
		close(pipes2[1]);
		
		create_command(elmt[idx], &cmdopt);
		exec(&cmdopt);
	}
	
	idx = 2;
	pids3 = fork();
	if (pids3 < 0)
		return ;
	if (pids3 == 0)
	{
		close(pipes1[0]);
		close(pipes1[1]);
		close(pipes2[1]);
		
		dup2(pipes2[0], STDIN_FILENO);
		close(pipes2[0]);
		
		create_command(elmt[idx], &cmdopt);
		exec(&cmdopt);
	}


	close(pipes1[0]);
	close(pipes1[1]);
	close(pipes2[0]);
	close(pipes2[1]);
	waitpid(pids1, NULL, 0);
	waitpid(pids2, NULL, 0);
	waitpid(pids3, NULL, 0);
	return ;

}
// -------------------

// PIPEX
void	pipex(char *input)
{
	char	**split_all;

	split_all = ft_split(input, '|');
	execute_all(split_all);
	//brut_test(split_all);
	free_d_array(split_all);
	return ;
}