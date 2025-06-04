/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:56:39 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/04 05:04:12 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_close(int fd)
{
	if (fd >= 0)
	{
		if (close(fd) == -1)
			ft_putstr_fd("Error closing file descriptor !\n", 2);
	}
	return (-1);
}
