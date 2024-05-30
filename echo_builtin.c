#include "minishell.h"

void    echo(t_data *data)
{
    int i;
    int newline;

    i = 1;
    newline = 0;
    if (data->input[i])
    {
        if (ft_strncmp(data->input[i], "-n\0", 2) == 0)
        {
            i++;
            newline = 1;
        }
        while (data->input[i])
        {
            printf("%s", data->input[i]);
            i++;
            if (data->input[i] != NULL)
                printf(" ");
        }
    }
    if (newline == 0)
            printf("\n");
}