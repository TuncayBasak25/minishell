/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:50:35 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:50:37 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	while (src[length] != '\0')
		length++;
	if (size <= 0)
		return (length);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int main()
{
	char src[] = "hello lhadj Ahmed";
	char dest[] = "hello le kabyle";
	char src2[] = "hello lhadj Ahmed";
	char dest2[] = "hello le kabyle";
	printf("%u\n", ft_strlcpy(dest, src, 0));
	printf("%s\n", dest);
	printf("%zu\n", strlcpy(dest2, src2, 0));
	printf("%s\n", dest2);
}
*/
