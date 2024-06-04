/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:52:53 by sp                #+#    #+#             */
/*   Updated: 2024/06/01 16:53:00 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	if (data->input[i])
	{
		if (ft_strncmp(data->input[i], "-n\0", 2) == 0)
		{
			i++;
			newline = 1;
		}
		while (data->input[i])
		{
			printf("%s", data->input[i]);
			i++;
			if (data->input[i] != NULL)
				printf(" ");
		}
	}
	if (newline == 0)
		printf("\n");
	data->exit_status = 0;
}
