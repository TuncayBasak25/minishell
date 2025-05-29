/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:39:48 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 22:49:30 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		size;
	char		*dest;

	if (!(s1) || !(s2))
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *) ft_calloc(size, sizeof(char));
	if (!(dest))
		return (NULL);
	dest[0] = '\0';
	size = ft_strlcat(dest, s1, size) + ft_strlcat(dest, s2, size);
	return (dest);
}
