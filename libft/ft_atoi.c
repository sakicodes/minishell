/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:12:23 by sp                #+#    #+#             */
/*   Updated: 2023/09/21 13:25:13 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	value;
	int	i;
	int	negcount;

	i = 0;
	value = 0;
	negcount = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			negcount = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		value = (value * 10) + (nptr[i] - 48);
		i++;
	}
	if (negcount == -1)
		value *= negcount;
	return (value);
}
