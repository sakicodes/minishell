/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:11:03 by sp                #+#    #+#             */
/*   Updated: 2024/05/21 23:11:04 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_environ(char *str)
{
	t_env	*env;
	char	*ptr;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		return (NULL);
	ptr = ft_strchr(str, '=');
	if (ptr)
	{
		env->key = ft_substr(str, 0, (ptr - str));
		env->value = ft_strdup(ptr + 1);
	}
	else
	{
		env->key = ft_strdup(str);
		env->value = NULL;
	}
	env->next = NULL;
	return (env);
}

void	add_env_back(t_env **environ, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*environ)
		*environ = new;
	else
	{
		last = *environ;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	remove_env(t_env **environ, t_env *del)
{
	t_env	*before;
	//t_env	*after;

	if (!environ || !*environ || !del)
		return ;
	if (*environ == del)
		*environ = (*environ)->next;
	else
	{
		before = *environ;
		while (before && before->next != del)
			before = before->next;
		//after = del->next;
		before->next = del->next;
	}
	free_ptr(del->key);
	free_ptr(del->value);
	del->next = NULL;
	free_ptr(del);
}

t_env	*initialise_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*new;

	head = NULL;
	new = NULL;
	i = 0;
	while (envp[i])
	{
		new = new_environ(envp[i]);
		if (!new)
		{
			free_envnode(head);
			exit_handler('m', NULL);
		}
		add_env_back(&head, new);
		i++;
	}
	return (head);
}
