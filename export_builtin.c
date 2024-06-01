/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:53:12 by sp                #+#    #+#             */
/*   Updated: 2024/06/01 16:57:02 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **env, int size)
{
	int		i;
	int		sorted;
	char	*temp;

	sorted = 0;
	while (env && size > 1 && sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
		size--;
	}
}

void	export_print(t_env *environ)
{
	char	**env_str;
	int		i;

	env_str = get_env_to_str(environ, 1);
	sort_env(env_str, get_env_size(environ));
	i = 0;
	while (env_str[i])
	{
		if (ft_strncmp(env_str[i], "_=\0", 2) != 0)
			printf("declare -x %s\n", env_str[i]);
		i++;
	}
}

int	export(t_data *data)
{
	if (data->input[1] == NULL)
		export_print(data->environ);
	return (1);
}
