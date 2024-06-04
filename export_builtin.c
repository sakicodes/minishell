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

int	valid_export_input(char *str)
{
	char	*equal_ptr;

	if (ft_isalpha(str[0]) == 0)
		return (1);
	equal_ptr = ft_strchr(str, '=');
	while (str < equal_ptr)
	{
		if (ft_isalnum(*str) == 0)
			return (1);
		str++;
	}
	return (0);
}

int	export(t_data *data)
{
	t_env	*ptr;
	char	**split;
	int	i;

	ptr = NULL;
	data->exit_status = 0;
	if (data->input[1] == NULL)
		export_print(data->environ);
	else
	{
		i = 1;
		while (data->input[i])
		{
			if (valid_export_input(data->input[i]) == 1)
			{
				printf("export: '%s': not a valid identifier.\n", data->input[i]);
				data->exit_status = 1;
			}
			else
			{
				split = ft_split(data->input[i], '=');
				ptr = get_env(data->environ, split[0]);
				if (ptr == NULL)
				{
					ptr = new_environ(data->input[i]);
					add_env_back(&data->environ, ptr);
				}
				else
				{
					free_ptr(ptr->value);
					if (split[1])
						ptr->value = ft_strdup(split[1]);
				}
				free_dblptr((void **)split);
			}
			i++;
		}
	}
	return (1);
}
