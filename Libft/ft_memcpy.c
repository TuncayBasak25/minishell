/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:23:04 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/16 14:23:06 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*p_src;
	unsigned char		*p_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = -1;
	p_src = src;
	p_dest = dest;
	while (++i < n)
		p_dest[i] = p_src[i];
	return (dest);
}
