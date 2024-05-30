#include "minishell.h"

int export(t_data *data)
{
    if (data->input[1] == NULL)
        export_print(data->environ);
    return (1);
}