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

int	unset(t_cmd *cmd, t_data *data)
{
	t_env	*ptr;
	int		i;

	data->exit_status = 0;
	if (!cmd->cmdwithflags[1])
		return (1);
	i = 1;
	while (cmd->cmdwithflags[i])
	{
		ptr = get_env(data->environ, cmd->cmdwithflags[i]);
		if (ptr)
			remove_env(&data->environ, ptr);
		i++;
	}
	return (1);
}
