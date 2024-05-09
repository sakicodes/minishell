/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:11:46 by sp                #+#    #+#             */
/*   Updated: 2023/09/10 15:32:25 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		ch;
	const unsigned char	*src;
	size_t				i;

	ch = (unsigned char)c;
	src = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (src[i] == ch)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
