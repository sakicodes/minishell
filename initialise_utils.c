/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:57:33 by sp                #+#    #+#             */
/*   Updated: 2024/06/01 17:57:36 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_handler(char c, char *cmd)
{
	if (c == 'o')
		perror("Opening file");
	else if (c == 'p')
		perror("Pipe error");
	else if (c == 'f')
		perror("Fork error");
	else if (c == 'e')
		perror("Execve error");
	else if (c == 'm')
		perror("Malloc error");
	else if (c == 'a')
	{
		write (2, "Command not found: ", 19);
		write (2, cmd, ft_strlen(cmd));
		perror("\nAccess error");
	}
	exit(EXIT_FAILURE);
}

char	*check_path(char **paths, char *cf)
{
	int		i;
	char	*joined;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			exit_handler('m', NULL);
		joined = ft_strjoin(temp, cf);
		if (!joined)
			exit_handler('m', NULL);
		free(temp);
		if (access(joined, F_OK | X_OK) == 0)
			return (joined);
		free(joined);
		i++;
	}
	if (!paths[i])
		exit_handler('a', cf);
	return (NULL);
}
