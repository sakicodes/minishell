/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:46:43 by sp                #+#    #+#             */
/*   Updated: 2023/12/09 21:16:47 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_opener(char *file, int check)
{
	int	fd;

	fd = -1;
	if (check == 1)
		fd = open(file, O_RDONLY);
	else if (check == 0)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (check == 2)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		exit_handler('o', NULL);
	return (fd);
}

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
	else if (c == 'i')
		write (2, "Invalid arguments\n", 18);
	exit(EXIT_FAILURE);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	heredoc_child(char *limit, int file)
{
	char	*line;

	while (1)
	{
		write (1, "here_doc>", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limit, ft_strlen(limit)) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, file);
		free(line);
	}
}

void	ft_heredoc(char **array)
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
		heredoc_child(array[2], pipe_fd[1]);
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}
