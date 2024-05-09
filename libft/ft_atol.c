/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:40:02 by sp                #+#    #+#             */
/*   Updated: 2024/02/20 18:40:06 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	int		i;
	long	value;
	int		negcount;

	i = 0;
	value = 0;
	negcount = 0;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negcount = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		value = (value * 10) + (nptr[i] - 48);
		i++;
	}
	if (negcount == -1)
		value *= negcount;
	return (value);
}
