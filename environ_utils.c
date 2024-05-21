/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:42:10 by sp                #+#    #+#             */
/*   Updated: 2024/05/21 16:42:12 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_index(t_env *environ, char *var)
{
	int	i;
	t_env	*current;

	i = 0;
	current = environ;
	while (current)
	{
		if (ft_strncmp(var, current->key, ft_strlen(var)) == 0)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}

t_env	*get_env(t_env *environ, char *var)
{
	t_env *current;

	current = environ;
	while (current)
	{
		if (ft_strncmp(var, current->key, ft_strlen(var)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

// int	change_env_var(t_data *data, char *var)
// {

// }
