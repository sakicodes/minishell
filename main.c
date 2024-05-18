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

void	change_directory(t_data *data)
{
	char	*ptr;
	char	*newpath;

	if (data->cmds->cmdwithflags[1])
	{
		if (ft_strncmp(data->cmds[0].cmdwithflags[1], "..\0", 2) == 0)
		{
			ptr = ft_strrchr(data->curr_dir, '/');
			newpath = ft_substr(data->curr_dir, 0, ptr - data->curr_dir);
			chdir(newpath);
			getcwd(data->curr_dir, 1024);
		}
	}
}

int	compare(t_data *data)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(data->line, "exit\0", 4) == 0)
	{
		data->death = 1;
		printf("exit, goodbye!\n");
	}
	else if (ft_strncmp(data->line, "pwd\0", 3) == 0)
	{
		printf("%s\n", data->curr_dir);
		ret = 1;
	}
	// else if (ft_strncmp(data->line, "cd\0", 2) == 0)
	// 	change_directory(data);
	return (ret);
}

int	initialise(t_data *data, char **envp)
{
	getcwd(data->curr_dir, 1024);
	update_env(data, envp);
	data->prompt = ft_strjoin(data->curr_dir, "> \0");
	if (!data->prompt)
		return (1);
	data->death = 0;
	return (0);
}

void	start(t_data *data)
{
	while (data->death == 0)
	{
		data->line = readline(data->prompt);
		if (ft_strlen(data->line) == 0)
			continue ;
		add_history(data->line);
		// parsing (split the line as necessary and save them to a char double ptr(char **input))
		if (compare(data) == 0)
		{
			// pipes, redirections, normal cmds etc etc (forking will be done as neccessary)
			// most prob will need to free the commands char double ptr 
		}
		free(data->line);
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
	free(data.prompt);
	return (0);
}
