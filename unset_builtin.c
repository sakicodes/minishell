#include "minishell.h"

int	unset(t_data *data)
{
	t_env	*ptr;

	if (!data->input[1])
		return (1);
	ptr = get_env(data->environ, data->input[1]);
	if (ptr)
		remove_env(&data->environ, ptr);
	return (1);
}
