/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:06:37 by sp                #+#    #+#             */
/*   Updated: 2024/06/08 15:06:42 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_data *data)
{
	t_env	*ptr;
	int		i;

	data->exit_status = 0;
	if (!data->input[1])
		return (1);
	i = 1;
	while (data->input[i])
	{
		ptr = get_env(data->environ, data->input[i]);
		if (ptr)
			remove_env(&data->environ, ptr);
		i++;
	}
	return (1);
}
