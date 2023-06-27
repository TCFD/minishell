/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:20:34 by wolf              #+#    #+#             */
/*   Updated: 2023/06/27 16:35:37 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	realloc_environ(int line, char *variable)
{
	int	idx;

	idx = 0;
	return ;

}

/* void	export_env_var(char *variable)
{
	char	**env_;
	int		idx;
	
	idx = -1;
	env_ = environ;
	if (getenv(variable))
	{
		while (environ[++idx])
		{
			if (ft_strncmp(env_[i], variable, ft_strlen(variable)) == 0
				&& env_[i][ft_strlen(variable)] == '=')
				break;
		}
		
	}
} */

void	verif_if_path_unset_at_start(void)
{
	if (!getenv("PATH"))
		//export PATH=...
		return ;
	return ;
}
