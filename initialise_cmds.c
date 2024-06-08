/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:20:18 by sp                #+#    #+#             */
/*   Updated: 2024/06/08 18:20:32 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable(char *cmd, t_env *environ)
{
	char	*exec;
	char	*temp;
	char	**split;
	int		i;
	t_env	*ptr;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	ptr = get_env(environ, "PWD\0");
	temp = ft_strjoin(ptr->value, "/\0");
	if (!temp)
		exit_handler('m', cmd);
	exec = ft_strjoin(temp, cmd);
	if (!exec)
		exit_handler('m', cmd);
	if (access(exec, F_OK | X_OK) == 0)
		return (exec);
	free_ptr(temp);
	free_ptr(exec);
	ptr = get_env(environ, "PATH\0");
	split = ft_split(ptr->value, ':');
	i = 0;
	while (split[i])
	{
		temp = ft_strjoin(split[i], "/\0");
		if (!temp)
			exit_handler('m', cmd);
		exec = ft_strjoin(temp, cmd);
		if (!exec)
			exit_handler('m', cmd);
		free_ptr(temp);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_dblptr((void **)split);
			return (exec);
		}
		free_ptr(exec);
		i++;
	}
	free_dblptr((void **)split);
	return (NULL);
}

t_cmd	*new_command(char *line, t_env *environ)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	if (!new)
		return (NULL);
	new->cmdwithflags = ft_split(line, ' ');
	new->cmd = ft_strdup(new->cmdwithflags[0]);
	new->executable = find_executable(new->cmd, environ);
	new->next = NULL;
	return (new);
}
