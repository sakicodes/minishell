#include "minishell.h"

int exit_program(t_data *data)
{
    int exit_number;

    exit_number = 0;
    if (data->input[1])
        exit_number = ft_atoi(data->input[1]);
    return (exit_number);
}