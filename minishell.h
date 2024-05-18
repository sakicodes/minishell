/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:12 by sp                #+#    #+#             */
/*   Updated: 2024/05/07 18:09:15 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <limits.h>

typedef struct s_cmd {
	char	*cmd;
	char	*executable;
	char	**cmdwithflags;
	struct s_cmd	*next;
}				t_cmd;

typedef	struct s_file {
	int	fd;
	struct s_file	*next;
}				t_file;

typedef struct s_data {
	char	curr_dir[1024];
	char	*prompt;
	char	*line;
	char	**input;
	char	**environ;
	char	*path;
	t_cmd	*cmds;
	t_file	*files;
	int		death;
}				t_data;

void	update_env(t_data *data, char **envp);
void	exit_handler(char c, char *cmd);
char	*getpath(char **envp);
char	*check_path(char **paths, char *cf);

#endif
