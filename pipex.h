/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:24:11 by sp                #+#    #+#             */
/*   Updated: 2024/05/09 21:24:16 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include "libft/libft.h"
# include "minishell.h"
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

int		file_opener(char *file, int check);
void	exit_handler(char c, char *cmd);
void	ft_free(char **array);
void	heredoc_child(char *limit, int file);
void	ft_heredoc(char **array);
char	*getpath(char **envp);
char	*check_path(char **paths, char *cf);
void	ft_execute(char *cmd, char **envp);
void	piping(char *cmd, char **envp);
int		file_ops(int index, char **array);

#endif
