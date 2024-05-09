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

void	compare(t_data *data)
{
	if (ft_strncmp(data->line, "exit\0", ft_strlen(data->line)) == 0)
	{
		data->death = 1;
		printf("exit, goodbye!\n");
	}
}

int	initialise(t_data *data, char **envp)
{
	getcwd(data->curr_dir, 1024);
	data->environ = envp;
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
		compare(data);
		// parsing (split the line as necessary and save them to a char double ptr)
		// shell processes: (forking should be done here i guess)
		// pipes, redirections, normal cmds etc etc
		// most prob will need to free the commands char double ptr 
		free(data->line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc != 1)
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
