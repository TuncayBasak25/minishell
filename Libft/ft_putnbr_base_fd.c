/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 06:18:06 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/31 06:34:54 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(unsigned long nbr, char *base, int fd)
{
	int		len;
	size_t	base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (base_len < 2)
		return (0);
	if (nbr >= base_len)
		len += ft_putnbr_base_fd(nbr / base_len, base, fd);
	len += ft_putchar_fd(base[nbr % base_len], fd);
	return (len);
}
