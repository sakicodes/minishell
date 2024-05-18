/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:22:25 by sp                #+#    #+#             */
/*   Updated: 2024/05/18 18:22:28 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_data *data)
{
	// if (< redirect input)
		dup2(data->files[0].fd, STDIN_FILENO);
	// else if (> redirect output)
		dup2(data->files[1].fd, STDOUT_FILENO);
	// else if (<< here docs)
	// else if (>> append output)
}
