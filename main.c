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
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

int	compare(t_data *data)
{
	int	ret;
	t_env	*ptr;
	t_env	*new;

	ret = 0;
	if (ft_strncmp(data->line, "exit\0", 4) == 0)
	{
		data->death = 1;
		ret = 1;
		printf("exit, goodbye!\n");
	}
	else if (ft_strncmp(data->line, "pwd\0", 3) == 0)
	{
		printf("%s\n", data->curr_dir);
		ret = 1;
	}
	else if (ft_strncmp(data->line, "cd\0", 2) == 0)
	{
		change_directory(data);
		ret = 1;
	}
	else if (ft_strncmp(data->line, "env\0", 3) == 0)
	{
		env_print(data->environ);
		ret = 1;
	}
	else if (ft_strncmp(data->line, "test\0", 4) == 0)
	{
		new = new_environ("TEST=1234567890abcdef\0");
		add_env_back(&data->environ, new);
		ptr = get_env(data->environ, "TEST\0");
		printf("%s=%s\n", ptr->key, ptr->value);
		ret = 1;
	}
	return (ret);
}

int	initialise(t_data *data, char **envp)
{
	getcwd(data->curr_dir, 1024);
	data->environ = initialise_env(envp);
	data->death = 0;
	data->exit_status = 0;
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
