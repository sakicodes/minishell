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

int	echo(t_cmd *cmd, t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	if (cmd->cmdwithflags[i])
	{
		if (ft_strncmp(cmd->cmdwithflags[i], "-n\0", 2) == 0)
		{
			i++;
			newline = 1;
		}
		while (cmd->cmdwithflags[i])
		{
			printf("%s", cmd->cmdwithflags[i]);
			i++;
			if (cmd->cmdwithflags[i] != NULL)
				printf(" ");
		}
	}
	if (newline == 0)
		printf("\n");
	data->exit_status = 0;
	return (1);
}
