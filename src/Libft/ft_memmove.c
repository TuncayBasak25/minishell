/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:29:55 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/16 14:29:57 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*p_src;
	unsigned char		*p_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = n;
	p_src = (unsigned const char *) src;
	p_dest = (unsigned char *) dest;
	if (dest > src)
	{
		while ((int)--i >= 0)
			p_dest[i] = p_src[i];
	}
	else
	{
		i = -1;
		while (++i < n)
			p_dest[i] = p_src[i];
	}
	return (dest);
}
