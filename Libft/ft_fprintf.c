/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 06:00:28 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/31 07:07:04 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define DEC "0123456789"
#define HEXL "0123456789abcdef"
#define HEXU "0123456789ABCDEF"

static int	handle_conversion(va_list args, char conv, int fd)
{
	if (conv == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (conv == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (conv == 'p')
	{
		ft_putstr_fd("0x", fd);
		return (2 + ft_putnbr_base_fd(va_arg(args, unsigned long), HEXL, fd));
	}
	else if (conv == 'd' || conv == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (conv == 'u')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), DEC, fd));
	else if (conv == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), HEXL, fd));
	else if (conv == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), HEXU, fd));
	else if (conv == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += handle_conversion(args, format[i], fd);
		}
		else
			count += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
