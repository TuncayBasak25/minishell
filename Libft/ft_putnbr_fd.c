/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:15:18 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/31 05:56:35 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		count;
	long	nb;

	count = 0;
	nb = n;
	if (nb == INT_MIN)
		return (write(fd, "-2147483648", 11));
	if (nb < 0)
	{
		count += ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
		count += ft_putnbr_fd(nb / 10, fd);
	count += ft_putchar_fd((nb % 10) + '0', fd);
	return (count);
}
