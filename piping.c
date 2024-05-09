/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:23:48 by sp                #+#    #+#             */
/*   Updated: 2024/05/09 21:23:56 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getpath(char **envp)
{
	char	*path;
	char	*cmp;
	int		i;
	int		j;

	i = 0;
	path = NULL;
	cmp = "PATH=\0";
	while (envp[i])
	{
		j = 0;
		while (*envp[i]++ == cmp[j])
		{
			if (cmp[j + 1] == '\0')
				path = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	return (path);
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

void	ft_execute(char *cmd, char **envp)
{
	char	*path;
	char	*validpath;
	char	**cf;
	char	**paths;

	path = getpath(envp);
	cf = ft_split(cmd, ' ');
	paths = ft_split(path, ':');
	if (!cf || !paths)
		exit_handler('m', NULL);
	validpath = check_path(paths, cf[0]);
	if (execve(validpath, cf, envp) == -1)
	{
		ft_free(cf);
		ft_free(paths);
		free(validpath);
		free(path);
		exit_handler('e', NULL);
	}
}

void	piping(char *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	process;

	if (pipe(pipe_fd) == -1)
		exit_handler('p', NULL);
	process = fork();
	if (process == -1)
		exit_handler('f', NULL);
	if (process == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		ft_execute(cmd, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

int	file_ops(int index, char **array)
{
	int	f1;
	int	f2;

	if (ft_strncmp(array[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (index < 6)
			exit_handler('i', NULL);
		f1 = 0;
		f2 = file_opener(array[index - 1], 2);
		ft_heredoc(array);
	}
	else
	{
		f1 = file_opener(array[1], 1);
		f2 = file_opener(array[index - 1], 0);
		dup2(f1, STDIN_FILENO);
		close(f1);
	}
	return (f2);
}
