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

int	change_directory(t_cmd *cmd, t_data *data)
{
	t_env	*ptr;
	// char	*pathptr;
	// char	*newpath;

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
	if (cmd->cmdwithflags[1])
	{
		if (chdir(cmd->cmdwithflags[1]) != 0)
		{
			perror("cd");
			data->exit_status = 1;
			return (1);
		}
	}
	else
	{
		ptr = get_env(data->environ, "HOME\0");
		if (chdir(ptr->value) != 0)
		{
			perror("cd");
			data->exit_status = 1;
			return (1);
		}
	}
	ptr = get_env(data->environ, "OLDPWD\0");
	free(ptr->value);
	ptr->value = ft_strdup(data->curr_dir);
	ptr = get_env(data->environ, "PWD\0");
	free(ptr->value);
	getcwd(data->curr_dir, 1024);
	ptr->value = ft_strdup(data->curr_dir);
	data->exit_status = 0;
	return (1);
}
