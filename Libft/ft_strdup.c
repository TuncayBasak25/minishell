/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:57:03 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 08:04:44 by rel-hass         ###   ########.fr       */
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

/*
#include <unistd.h>

int main(void)
{
	char *src = "Hello lhadj !";
	char *dest;

	dest = ft_strdup(src);
	write(1, src, ft_strlen(src));
	write(1, "\n", 1);
	write(1, dest, ft_strlen(dest));
	write(1, "\n", 1);
	free(dest);
	return 0;
}
*/
