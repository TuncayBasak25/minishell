/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:57:03 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 22:49:23 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = -1;
	if (!s)
		return (NULL);
	dest = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!(dest))
		return (NULL);
	while (s[++i] != '\0')
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}
