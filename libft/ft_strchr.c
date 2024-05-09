/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:51:12 by sp                #+#    #+#             */
/*   Updated: 2023/09/19 21:35:42 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	char			*str;

	ch = (unsigned char)c;
	str = (char *)s;
	while (*str)
	{
		if ((unsigned char)*str == ch)
			return (str);
		str++;
	}
	if (ch == '\0')
		return (str);
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
	printf("ori: %p\n", strchr("teste", '\0'));
	printf("result: %p\n", ft_strchr("teste",'\0'));
	return (0);
}*/
