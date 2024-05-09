/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:27:48 by sp                #+#    #+#             */
/*   Updated: 2023/09/19 17:56:09 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*str;
	int		lencount;

	ch = (char)c;
	str = (char *)s;
	lencount = ft_strlen(s);
	if (c == '\0')
		return (str + lencount);
	while (lencount >= 0)
	{
		if (str[lencount] == ch)
			return (str + lencount);
		lencount--;
	}
	return (NULL);
}
