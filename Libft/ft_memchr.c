/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:53:41 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:53:43 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned const char	*p;

	i = -1;
	p = s;
	while (++i < n)
	{
		if (*p == (unsigned char) c)
			return ((char *) p);
		p++;
	}
	return (NULL);
}
