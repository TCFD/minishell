/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:39:21 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/07 14:12:39 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_output(char **tab, int *stdout_save, int *filefd, int which_case)
{
	int			i;

	*stdout_save = dup(STDOUT_FILENO);
	if (*stdout_save == -1)
		return (perror("Failed to save stdout"), 1);
	if (which_case == 1)
		*filefd = open(tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		*filefd = open(tab[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (*filefd == -1)
		return (perror("Failed to open file"), 1);
	if (dup2(*filefd, STDOUT_FILENO) == -1)
		return (perror("Failed to redirect stdout"), 1);
	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	return (0);
}

void	restore_fd(int position, int stdout_save, int filefd)
{
	if (position > -1)
	{
		if (dup2(stdout_save, STDOUT_FILENO) == -1)
			return (perror("Failed to restore stdout"));
		close(filefd);
		close(stdout_save);
	}
}

t_list	*remove_redirection(t_cmd_and_opt *cmdopt)
{
	int		i;
	char	*last_one;
	
	i = -1;
	last_one = ft_strdup("");
	while (cmdopt->opt_ty_tb.tab[++i])
	{
		if (ft_strncmp(cmdopt->opt_ty_tb.tab[i], SIMPLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i]))
			|| ft_strncmp(cmdopt->opt_ty_tb.tab[i], DOUBLE_R_RAFTER,
			ft_strlen(cmdopt->opt_ty_tb.tab[i])))
		{
			free(last_one);
			last_one = ft_strdup(cmdopt->opt_ty_tb.tab[i]);
			if (close(open(cmdopt->opt_ty_tb.tab[i + 1])))
		}
		else
		{
			
		}
	}
}

int	search_redirections(t_cmd_and_opt *cmdopt, int *stdout_save,
	int *filefd, long int *position)
{
	//*position = search_d_tab(cmdopt, ">>");
	remove_redirection(cmdopt);	
	return (0);
}
