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

void	free_file(t_file *file, int redir)
{
	t_file	*temp;

	while (file)
	{
		temp = file;
		file= file->next;
		if (redir != 3)
			close(temp->fd);
		free_ptr(temp->filename);
		free(temp);
	}
}

void	free_nodes(t_node *head)
{
	t_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free_cmd(temp->cmd);
		free_file(temp->file, temp->redir);
		free(temp);
	}
}

void	free_data(t_data *data)
{
	free_ptr(data->prompt);
	free_ptr(data->line);
	free_nodes(data->node);
	free_envnode(data->environ);
}
