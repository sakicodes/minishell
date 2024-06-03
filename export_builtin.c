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
	free_dblptr((void **)env_str);
}

int	export(t_data *data)
{
	t_env	*ptr;
	char	**split;
	int	i;

	ptr = NULL;
	if (data->input[1] == NULL)
		export_print(data->environ);
	else
	{
		i = 1;
		while (data->input[i])
		{
			split = ft_split(data->input[i], '=');
			if (!split[0] && data->input[i][0] == '=')
			{
				printf("export: '=': not a valid identifier.\n");
				data->exit_status = 1;
				break ;
			}
			ptr = get_env(data->environ, split[0]);
			if (ptr == NULL)
			{
				ptr = new_environ(data->input[i]);
				add_env_back(&data->environ, ptr);
			}
			else
			{
				free_ptr(ptr->value);
				ptr->value = ft_strdup(split[1]);
			}
			free_dblptr((void **)split);
			i++;
		}
	}
	return (1);
}
