#include "minishell.h"

void    echo(t_data *data)
{
    int i;

    i = 1;
    if (ft_strncmp(data->input[1], "-n\0", 2) == 0)
        i++;
    while (data->input[i])
    {
        printf("%s", data->input[i]);
        i++;
        if (data->input[i] != NULL)
            printf(" ");
    }
    if (ft_strncmp(data->input[1], "-n\0", 2) != 0)
            printf("\n");
}