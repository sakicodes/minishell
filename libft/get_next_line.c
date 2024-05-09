/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:45:45 by sp                #+#    #+#             */
/*   Updated: 2023/10/12 19:03:05 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	eof_checker(char *saved, int bytes_read)
{
	if (!saved || (bytes_read == 0 && !ft_strlen(saved)))
	{
		free(saved);
		return (1);
	}
	return (0);
}

static char	*gnl_add(char *saved, const char *buf)
{
	char	*temp;

	if (!saved)
		return (ft_substr(buf, 0, ft_strlen(buf)));
	temp = saved;
	saved = ft_strjoin(temp, buf);
	free(temp);
	return (saved);
}

static char	*gnl_read(int fd, char *saved)
{
	char	*buf;
	int		bytes_read;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buf, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(saved);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		saved = gnl_add(saved, buf);
	}
	free(buf);
	if (eof_checker(saved, bytes_read))
		return (NULL);
	return (saved);
}

static char	*gnl_extract_and_flush(char **saved)
{
	char	*line;
	char	*temp;
	size_t	savedlen;
	size_t	remlen;

	savedlen = ft_strlen(*saved);
	if (!ft_strchr(*saved, '\n'))
	{
		line = ft_substr(*saved, 0, savedlen);
		free(*saved);
		*saved = NULL;
	}
	else
	{
		remlen = ft_strlen(ft_strchr(*saved, '\n') + 1);
		line = ft_substr(*saved, 0, savedlen - remlen);
		temp = *saved;
		*saved = ft_substr((ft_strchr(*saved, '\n') + 1), 0, remlen);
		free(temp);
	}
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved[1024];
	char		*nextline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = gnl_read(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	nextline = gnl_extract_and_flush(&saved[fd]);
	if (!nextline)
		return (NULL);
	return (nextline);
}
