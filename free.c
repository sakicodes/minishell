/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:31:58 by sp                #+#    #+#             */
/*   Updated: 2024/05/21 15:32:06 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_dblptr(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free_ptr(ptr[i]);
			i++;
		}
		free(ptr);
		ptr = NULL;
	}
}

void	free_envnode(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free_ptr(temp->key);
		free_ptr(temp->value);
		free(temp);
	}
}

void	free_cmd(t_cmd *head)
{
	t_cmd	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free_ptr(temp->cmd);
		free_ptr(temp->executable);
		free_dblptr((void **)temp->cmdwithflags);
		free(temp);
	}
}
