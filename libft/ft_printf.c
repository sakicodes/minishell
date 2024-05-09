/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sp <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:38:58 by sp                #+#    #+#             */
/*   Updated: 2023/10/01 15:48:42 by sp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_arg(char spec, va_list ptr)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += ft_putchar(va_arg(ptr, int));
	else if (spec == 's')
		count += ft_putstr(va_arg(ptr, char *));
	else if (spec == 'd' || spec == 'i')
		count += ft_putnbr(va_arg(ptr, int));
	else if (spec == 'u')
		count += ft_uitop(va_arg(ptr, unsigned int));
	else if (spec == 'x')
		count += ft_uitoxp(va_arg(ptr, unsigned int));
	else if (spec == 'X')
		count += ft_uitoxupperp(va_arg(ptr, unsigned int));
	else if (spec == 'p')
		count += ft_putptr(va_arg(ptr, unsigned long int));
	else if (spec == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ptr;
	int		printcount;
	int		i;

	va_start(ptr, format);
	printcount = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i])
				printcount += ft_print_arg(format[i], ptr);
			else
				break ;
		}
		else
			printcount += ft_putchar(format[i]);
		i++;
	}
	va_end(ptr);
	return (printcount);
}
