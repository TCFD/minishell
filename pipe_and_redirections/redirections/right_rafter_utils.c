/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:39:21 by rciaze            #+#    #+#             */
/*   Updated: 2023/07/11 16:40:06 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* int	redirect_output(char **tab, int *stdout_save, int *filefd, int which_case)
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

t_list	*remove_redirection(t_cmd_and_opt *cmdopt,  long int *position)
{
	int		i;
	t_list	**start;
	t_list	*return_list;

	i = -1;
	start = &return_list;
	while (cmdopt->opt_ty_tb.tab[++i])
	{
		
	}
	return (*start);
}*/

char	**list_to_d_tab(t_list *list)
{
	int	i;
	char	**tab;
	
	tab = ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
	i = 0;
	while (list)
	{
		tab[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	count_redirections(char **tab, char *type)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (tab[++i])
	{
		if (ft_strnstr(tab[i], SIMPLE_R_RAFTER, ft_strlen(tab[i])) && type[i] != SIMPLE_Q && type[i] != DOUBLE_Q)
			counter++;
	}
	return (counter);
}

int	search_redirections(t_cmd_and_opt *cmdopt, int *stdout_save,
	int *filefd, long int *position)
{
	//t_list	*list;
	int		counter;
	(void)stdout_save;
	(void)filefd;
	(void)position;
	
	
	counter = count_redirections(cmdopt->opt_ty_tb.tab, cmdopt->opt_ty_tb.type);
	printf("%d\n", counter);
	//list = remove_redirection(cmdopt, position);
	//free_d_array(cmdopt->opt_ty_tb.tab);
	//cmdopt->opt_ty_tb.tab = list_to_d_tab(list);
	return (0);
}
