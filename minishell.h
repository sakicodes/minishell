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
	char			*cmd;
	char			*executable;
	char			**cmdwithflags;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_file {
	char			*filename;
	int				fd;
	struct s_file	*next;
}				t_file;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_data {
	char			curr_dir[1024];
	char			*prompt;
	char			*line;
	char			**input;
	char			**env;
	t_cmd			*cmds;
	t_file			*files;
	t_env			*environ;
	int				death;
	unsigned int	exit_status;
}				t_data;

// free functions add under
void	free_ptr(void *ptr);
void	free_dblptr(void **ptr);
void	free_envnode(t_env *head);
void	free_cmd(t_cmd *head);

// initialise
void	increase_shell_level(t_env *environ);
char	*find_executable(char *cmd, t_env *environ);
t_cmd	*new_command(char *line, t_env *environ);

// handling of environ
t_env	*new_environ(char *str);
t_env	*initialise_env(char **envp);
void	exit_handler(char c, char *cmd);
t_env	*get_env(t_env *environ, char *var);
int		get_env_index(t_env *environ, char *var);
void	add_env_back(t_env **environ, t_env *new);
void	remove_env(t_env **environ, t_env *del);
int		get_env_size(t_env *head);
char	**get_env_to_str(t_env *environ, int type);

// builtins
int		env_print(t_env *environ);
int		change_directory(t_cmd *cmd, t_data *data);
int		exit_program(unsigned int *exit_status, t_cmd *cmd);
int		echo(t_cmd *cmd, t_data *data);
int		export(t_cmd *cmd, t_data *data);
int		unset(t_cmd *cmd, t_data *data);

char	*check_path(char **paths, char *cf);

#endif
