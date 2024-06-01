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
	int		i;
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
	t_env	*current;

	current = environ;
	while (current)
	{
		if (ft_strncmp(var, current->key, ft_strlen(var)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	get_env_size(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*env_to_str(t_env *current, int type)
{
	char	*str;
	char	*temp;

	str = ft_strdup(current->key);
	if (current->value)
	{
		if (type == 1)
			temp = ft_strjoin(str, "=\"\0");
		else
			temp = ft_strjoin(str, "=\0");
		free_ptr(str);
		str = ft_strjoin(temp, current->value);
		free_ptr(temp);
		if (type == 1)
		{
			temp = ft_strjoin(str, "\"\0");
			free_ptr(str);
			str = ft_strdup(temp);
			free_ptr(temp);
		}
	}
	return (str);
}

char	**get_env_to_str(t_env *environ, int type)
{
	int		objs;
	char	**array;
	t_env	*current;
	int		i;

	if (environ == NULL)
		return (NULL);
	objs = get_env_size(environ);
	array = malloc(sizeof(char *) * (objs + 1));
	if (!array)
		return (NULL);
	current = environ;
	i = 0;
	while (current)
	{
		array[i] = env_to_str(current, type);
		i++;
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}
