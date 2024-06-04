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

void	env_print(t_env *environ)
{
	t_env	*current;

	current = environ;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

int	compare(t_data *data)
{
	int	ret;
	char	*cmd;
	int	len;

	ret = 0;
	cmd = data->input[0];
	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "exit\0", len) == 0)
	{
		data->death = 1;
		data->exit_status = exit_program(data);
		ret = 1;
		printf("exit, goodbye!\n");
	}
	else if (ft_strncmp(cmd, "pwd\0", len) == 0)
	{
		printf("%s\n", data->curr_dir);
		ret = 1;
	}
	else if (ft_strncmp(cmd, "cd\0", len) == 0)
	{
		change_directory(data);
		ret = 1;
	}
	else if (ft_strncmp(cmd, "env\0", len) == 0)
	{
		env_print(data->environ);
		data->exit_status = 0;
		ret = 1;
	}
	else if (ft_strncmp(cmd, "echo\0", len) == 0)
	{
		echo(data);
		ret = 1;
	}
	else if (ft_strncmp(cmd, "export\0", len) == 0)
		ret = export(data);
	else if (ft_strncmp(cmd, "unset\0", len) == 0)
		ret = unset(data);
	else if (ft_strncmp(data->line, "test $?\0", 7) == 0)
	{
		ret = 1;
		printf("%d\n", data->exit_status);
	}
	else if (ft_strncmp(data->line, "test blah\0", 9) == 0)
	{
		ret = 1;
		printf("%s\n", data->line);
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

void	start(t_data *data)
{
	while (data->death == 0)
	{
		data->prompt = get_prompt(data->curr_dir);
		data->line = readline(data->prompt);
		if (ft_strlen(data->line) == 0)
			continue ;
		add_history(data->line);
		data->input = ft_split(data->line, ' ');
		// parsing (split the line as necessary and save them to a char double ptr(char **input))
		if (compare(data) == 0)
		{
			// pipes, redirections, normal cmds etc etc (forking will be done as neccessary)
			// most prob will need to free the commands char double ptr 
		}
		free_ptr(data->line);
		free_ptr(data->prompt);
		free_dblptr((void **)data->input);
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
