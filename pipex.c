/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:22:57 by sp                #+#    #+#             */
/*   Updated: 2023/12/09 22:27:06 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex(t_data *data)
{
	int	f2;
	int	i;

	// f2 = file_ops(argc, argv);
	// if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	// 	i = 3;
	// else
	// 	i = 2;
	while (i < (data->num_of_inputs - 2))
		piping(data->input[i++], data->environ);
	dup2(f2, STDOUT_FILENO);
	close(f2);
	ft_execute(data->input[data->num_of_inputs - 2], data->environ);
	wait(NULL);
	return (0);
}

// to be worked on
