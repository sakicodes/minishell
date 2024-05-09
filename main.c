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

int	initialise(t_data *data)
{
	getcwd(data->curr_dir, 1024);
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
		printf("this is the line: %s\n", data->line);
		printf("line length: %d\n", (int)ft_strlen(data->line));
		compare(data);
		// parsing
		// shell processes:
		// pipes, redirections, normal cmds etc etc
		free(data->line);
	}
}

int main(void)
{
	t_data data;

	if (initialise(&data) == 1)
	{
		printf("initialising failed\n");
		return (1);
	}
	// signal handling
	start(&data);
	free(data.prompt);
	return (0);
}
