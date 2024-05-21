/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:16:46 by sp                #+#    #+#             */
/*   Updated: 2024/05/21 18:16:48 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(t_data *data)
{
	t_env	*ptr;
	char	*pathptr;
	char	*newpath;

	// if (data->cmds->cmdwithflags[1])
	// {
	// 	if (ft_strncmp(data->cmds[0].cmdwithflags[1], "..\0", 2) == 0)
	// 	{
	// 		ptr = ft_strrchr(data->curr_dir, '/');
	// 		newpath = ft_substr(data->curr_dir, 0, ptr - data->curr_dir);
	// 		chdir(newpath);
	// 	}
	// 	else
	// 		chdir(data->cmds[0].cmdwithflags[1]);
	// }
	// else
	// {
	// 	ptr = get_env_var(data->environ, "HOME=\0");
	// 	chdir(ptr);
	// }
	// getcwd(data->curr_dir, 1024);
	if (data->input[1])
	{
		if (ft_strncmp(data->input[1], "..\0", 2) == 0)
		{
			pathptr = ft_strrchr(data->curr_dir, '/');
			newpath = ft_substr(data->curr_dir, 0, pathptr - data->curr_dir);
			chdir(newpath);
			free(newpath);
		}
		else
			chdir(data->input[1]);
	}
	else
	{
		ptr = get_env(data->environ, "HOME\0");
		chdir(ptr->value);
	}
	getcwd(data->curr_dir, 1024);
}
