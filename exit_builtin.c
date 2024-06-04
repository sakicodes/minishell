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

int	exit_program(t_data *data)
{
	int	exit_number;

	exit_number = data->exit_status;
	if (data->input[1])
	{
		exit_number = ft_atoi(data->input[1]);
		if (exit_number < 0 || exit_number > 255)
			exit_number = exit_number % 256;
	}
	return (exit_number);
}
