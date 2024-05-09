/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxxp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:25:38 by sp                #+#    #+#             */
/*   Updated: 2023/10/01 15:13:27 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_converthex(int n)
{
	if (n >= 0 && n <= 9)
		return (n + 48);
	if (n >= 10 && n <= 16)
		return ((n - 10) + 97);
	return (n);
}

int	ft_converthexupper(int n)
{
	if (n >= 0 && n <= 9)
		return (n + 48);
	if (n >= 10 && n <= 16)
		return ((n - 10) + 65);
	return (n);
}

int	ft_uitoxp(long n)
{
	int		count;

	count = 0;
	if (n < 0)
		n = (n % 4294967296);
	if (n == 0)
		return (ft_putchar(n + 48));
	if (n >= 16)
		count += ft_uitoxp(n / 16);
	count += ft_putchar(ft_converthex(n % 16));
	return (count);
}

int	ft_uitoxupperp(long n)
{
	int		count;

	count = 0;
	if (n < 0)
		n = (n % 4294967296);
	if (n == 0)
		return (ft_putchar(n + 48));
	if (n >= 16)
		count += ft_uitoxupperp(n / 16);
	count += ft_putchar(ft_converthexupper(n % 16));
	return (count);
}

int	ft_putptr(unsigned long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (write (1, "(nil)", 5));
	count += ft_putstr("0x");
	count += ft_uitoxp(n);
	return (count);
}
