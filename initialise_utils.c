#include "minishell.h"

void	update_env(t_data *data, char **envp)
{
	data->environ = envp;
	data->path = getpath(envp);
}

void	exit_handler(char c, char *cmd)
{
	if (c == 'o')
		perror("Opening file");
	else if (c == 'p')
		perror("Pipe error");
	else if (c == 'f')
		perror("Fork error");
	else if (c == 'e')
		perror("Execve error");
	else if (c == 'm')
		perror("Malloc error");
	else if (c == 'a')
	{
		write (2, "Command not found: ", 19);
		write (2, cmd, ft_strlen(cmd));
		perror("\nAccess error");
	}
	exit(EXIT_FAILURE);
}

char	*getpath(char **envp)
{
	char	*path;
	char	*cmp;
	int		i;
	int		j;

	i = 0;
	path = NULL;
	cmp = "PATH=\0";
	while (envp[i])
	{
		j = 0;
		while (*envp[i]++ == cmp[j])
		{
			if (cmp[j + 1] == '\0')
				path = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	return (path);
}

char	*check_path(char **paths, char *cf)
{
	int		i;
	char	*joined;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			exit_handler('m', NULL);
		joined = ft_strjoin(temp, cf);
		if (!joined)
			exit_handler('m', NULL);
		free(temp);
		if (access(joined, F_OK | X_OK) == 0)
			return (joined);
		free(joined);
		i++;
	}
	if (!paths[i])
		exit_handler('a', cf);
	return (NULL);
}
