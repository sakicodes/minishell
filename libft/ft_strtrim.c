/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:47:31 by sp                #+#    #+#             */
/*   Updated: 2023/11/04 14:20:36 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	s1end;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	s1end = ft_strlen(s1) - 1;
	while (s1[i] && check(s1[i], set))
		i++;
	while (s1end > 0 && check(s1[s1end], set))
		s1end--;
	if (i > s1end)
		trimmed = malloc(sizeof(char));
	else
		trimmed = malloc(sizeof(char) * (s1end - i + 2));
	if (trimmed == NULL || !s1)
		return (NULL);
	while (i <= s1end && *s1)
		trimmed[j++] = s1[i++];
	trimmed[j] = '\0';
	return (trimmed);
}
