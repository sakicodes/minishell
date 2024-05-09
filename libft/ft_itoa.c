/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:49:51 by sp                #+#    #+#             */
/*   Updated: 2023/09/19 18:20:53 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	insert_string(char *str, int n)
{
	int	i;

	if (str[0] == '-')
		i = 1;
	else
		i = 0;
	if (n == 0)
		str[i++] = '0';
	else
	{
		while (n != 0)
		{
			str[i] = (n % 10) + 48;
			n /= 10;
			i++;
		}
	}
	str[i] = '\0';
}

static void	reverse_string(char *str)
{
	size_t	left;
	size_t	right;
	char	temp;

	right = ft_strlen(str) - 1;
	if (str[0] == '-')
		left = 1;
	else
		left = 0;
	while (left < right)
	{
		temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = count_digits(n);
	str = malloc(sizeof(char) * (digits + 1 + (n < 0)));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	insert_string(str, n);
	reverse_string(str);
	return (str);
}
