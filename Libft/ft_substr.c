/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:09:56 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 22:50:23 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*dest;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_calloc(1, sizeof(char)));
	else if (len > size - start)
		len = size - start;
	dest = (char *) ft_calloc(len + 1, sizeof(char));
	if (!(dest))
		return (NULL);
	len = ft_strlcpy(dest, &s[start], len + 1);
	return (dest);
}
