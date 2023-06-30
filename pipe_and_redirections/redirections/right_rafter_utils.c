/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_rafter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbp15 <zbp15@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:39:21 by rciaze            #+#    #+#             */
/*   Updated: 2023/06/30 18:08:15 by zbp15            ###   ########.fr       */
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

int	search_redirections(t_cmd_and_opt *cmdopt, int *stdout_save,
	int *filefd, long int *position)
{
	*position = search_d_tab(cmdopt, ">>");
	if (*position > -1)
		if (redirect_output(cmdopt->opt_tab.tab + *position, stdout_save,
				filefd, 2))
			return (1);
	if (*position <= -1)
	{
		*position = search_d_tab(cmdopt, ">");
		if (*position > -1)
			if (redirect_output(cmdopt->opt_tab.tab + *position, stdout_save,
					filefd, 1))
				return (1);
	}	
	return (0);
}

void	dup_d_array(char **src, char ***dest, int *j)
{
	*j = 0;
	while (src[*j])
		*j += 1;
	dest[0] = ft_calloc(sizeof(char *), *j + 1);
	*j = -1;
	while (src[++*j])
		dest[0][*j] = ft_strdup(src[*j]);
	dest[0][*j] = NULL;
}

void	realloc_chevrons(t_cmd_and_opt *cmdopt, int start, int end)
{
	char	**temp;
	int		j;
	int		temp_counter;

	temp = NULL;
	dup_d_array(cmdopt->opt_tab.tab, &temp, &j);
	free_d_array(cmdopt->opt_tab.tab);
	cmdopt->opt_tab.tab = ft_calloc(sizeof(char *), j - (end - start) + 1);
	temp_counter = 0;
	j = -1;
	while (temp[++j])
	{
		if (j == start)
			while (j < end)
				j++;
		cmdopt->opt_tab.tab[temp_counter] = ft_strdup(temp[j]);
		temp_counter++;
	}
	cmdopt->opt_tab.tab[temp_counter] = NULL;
	free_d_array(temp);
}

int	search_d_tab(t_cmd_and_opt *cmdopt, char *c)
{
	int			i;
	int			j;
	int			tmp;

	i = -1;
	while (cmdopt->opt_tab.tab[++i])
	{
		if (ft_strnstr(cmdopt->opt_tab.tab[i], c, ft_strlen(cmdopt->opt_tab.tab[i])) && cmdopt->opt_tab.type[i] == INTERPRETABLE)
		{
			j = i;
			tmp = i;
			while (cmdopt->opt_tab.tab[++j])
			{
				if (ft_strnstr(cmdopt->opt_tab.tab[j], c, ft_strlen(cmdopt->opt_tab.tab[j])) && cmdopt->opt_tab.type[j] == INTERPRETABLE)
				{
					close(open(cmdopt->opt_tab.tab[tmp + 1], O_CREAT, 0666));
					tmp = j;
				}
			}
			realloc_chevrons(cmdopt, i, tmp);
			return (i);
		}
	}
	return (-1);
}
