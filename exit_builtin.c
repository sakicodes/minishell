/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:52:32 by sp                #+#    #+#             */
/*   Updated: 2024/06/01 16:52:46 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_program(unsigned int *exit_status, t_cmd *cmd)
{
	unsigned int	exit_number;

	exit_number = *exit_status;
	if (cmd->cmdwithflags[1])
	{
		exit_number = ft_atoi(cmd->cmdwithflags[1]);
		if (exit_number > 255)
			exit_number = exit_number % 256;
	}
	*exit_status = exit_number;
	return (1);
}
