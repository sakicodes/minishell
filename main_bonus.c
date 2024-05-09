/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:22:57 by sp                #+#    #+#             */
/*   Updated: 2023/12/09 22:27:06 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	f2;
	int	i;

	if (argc < 5)
		exit_handler('i', NULL);
	f2 = file_ops(argc, argv);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		i = 3;
	else
		i = 2;
	while (i < (argc - 2))
		pipex(argv[i++], envp);
	dup2(f2, STDOUT_FILENO);
	close(f2);
	ft_execute(argv[argc - 2], envp);
	wait(NULL);
	return (0);
}
