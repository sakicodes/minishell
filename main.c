/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:06:45 by sp                #+#    #+#             */
/*   Updated: 2024/05/07 18:06:48 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_print(t_env *environ)
{
	t_env	*current;

	current = environ;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (1);
}

int	compare(t_cmd *cmd, t_data *data)
{
	int	ret;
	char	*command;
	int	len;

	ret = 0;
	command = cmd->cmdwithflags[0];
	len = ft_strlen(command);
	if (ft_strncmp(command, "exit\0", len) == 0)
	{
		data->death = 1;
		ret = exit_program(&data->exit_status, cmd);
		printf("exit, goodbye!\n");
	}
	else if (ft_strncmp(command, "pwd\0", len) == 0)
		ret = printf("%s\n", data->curr_dir);
	else if (ft_strncmp(command, "cd\0", len) == 0)
		ret = change_directory(cmd, data);
	else if (ft_strncmp(command, "env\0", len) == 0)
	{
		ret = env_print(data->environ);
		data->exit_status = 0;
	}
	else if (ft_strncmp(command, "echo\0", len) == 0)
		ret = echo(cmd, data);
	else if (ft_strncmp(command, "export\0", len) == 0)
		ret = export(cmd, data);
	else if (ft_strncmp(command, "unset\0", len) == 0)
		ret = unset(cmd, data);
	else if (ft_strncmp(data->line, "test $?\0", 7) == 0)
	{
		ret = 1;
		printf("%d\n", data->exit_status);
	}
	return (ret);
}

int	initialise(t_data *data, char **envp)
{
	getcwd(data->curr_dir, 1024);
	data->environ = initialise_env(envp);
	data->death = 0;
	data->exit_status = 0;
	increase_shell_level(data->environ);
	return (0);
}

char	*get_prompt(char *curr_dir)
{
	char	*prompt;

	prompt = ft_strjoin(curr_dir, "> \0");
	if (!prompt)
		return (NULL);
	return (prompt);
}

void	open_subprocess(t_cmd *command, t_env *environ, unsigned int *exit_status)
{
	char	**envp;
	pid_t	process;
	int	status;

	status = 0;
	process = fork();
	if (process == -1)
		exit_handler('f', NULL);
	if (process == 0)
	{
		envp = get_env_to_str(environ, 0);
		if (execve(command->executable, command->cmdwithflags, envp) == -1)
		{
			free_dblptr((void **)envp);
			exit_handler('e', NULL);
		}
	}
	else
	{
		waitpid(process, &status, 0);
		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
		else
			*exit_status = 1;
	}
}

int	file_opener(char *file, int type)
{
	int	fd;

	fd = -1;
	if (type == 1)
		fd = open(file, O_RDONLY);
	else if (type == 2)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (type == 3)
		fd = STDIN_FILENO;
	else if (type == 4)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		exit_handler('o', NULL);
	return (fd);
}

t_file	*new_file(char	*line, int redir)
{
	t_file	*new;

	new = malloc(sizeof(t_file) * 1);
	if (!new)
		return (NULL);
	new->filename = ft_strdup(line);
	new->fd = file_opener(new->filename, redir);
	new->next = NULL;
	return (new);
}

t_node	*new_node(char *line, char *next, int index, t_env *environ)
{
	t_node	*ret;
	char	**split;

	//ret->line = line;
	ret = malloc(sizeof(t_node) * 1);
	if (!ret)
		return (NULL);
	if (ft_strchr(line, '<'))
	{
		if (ft_strncmp(ft_strchr(line, '<'), "<<\0", 2) == 0)
			ret->redir = 3;
		else
			ret->redir = 1;
		split = ft_split(line, '<');
	}
	else if (ft_strchr(line, '>'))
	{
		if (ft_strncmp(ft_strchr(line, '>'), ">>\0", 2) == 0)
			ret->redir = 4;
		else
			ret->redir = 2;
		split = ft_split(line, '>');
	}
	else
	{
		ret->redir = 0;
		ret->cmd = new_command(line, environ);
		ret->file = NULL;
		split = ft_split(line, ' ');
	}
	if (ret->redir != 0)
	{
		ret->cmd = new_command(split[0], environ);
		ret->file = new_file(split[1], ret->redir);
	}
	if (next == NULL && index == 0)
		ret->pipe_type = 0;
	else if (next == NULL && index != 0)
		ret->pipe_type = 3;
	else
	{
		if (index == 0)
			ret->pipe_type = 1;
		else
			ret->pipe_type = 2;
	}
	ret->next = NULL;
	return (ret);
}

void	add_node_back(t_node **head, t_node *new)
{
	t_node	*last;

	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last= last->next;
		last->next = new;
	}
}

t_node	*initialise_nodes(char *line, t_env *environ)
{
	char	**split;
	int	i;
	t_node	*new;
	t_node	*head;

	i = 0;
	new = NULL;
	head = NULL;
	split = ft_split(line, '|');
	while (split[i])
	{
		new = new_node(split[i], split[i + 1], i, environ);
		if (!new)
		{
			free_nodes(head);
			exit_handler('m', NULL);
		}
		add_node_back(&head, new);
		i++;
	}
	return (head);
}

void	start(t_data *data)
{
	while (data->death == 0)
	{
		data->prompt = get_prompt(data->curr_dir);
		data->line = readline(data->prompt);
		if (ft_strlen(data->line) == 0)
			continue ;
		add_history(data->line);
		data->node = initialise_nodes(data->line, data->environ);
		// if (compare(data->cmds, data) == 0)
		// {
		// 	open_subprocess(data->cmds, data->environ, &data->exit_status);
		// }
		free_ptr(data->line);
		free_ptr(data->prompt);
		free_cmd(data->cmds);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc != 1 || argv[1] != NULL)
	{
		printf("No aruguments please !\n");
		return (1);
	}
	if (initialise(&data, envp) == 1)
	{
		printf("initialising failed\n");
		return (1);
	}
	// signal handling
	start(&data);
	free_envnode(data.environ);
	return (data.exit_status);
}
