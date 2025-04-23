/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:50:57 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:50:59 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;
	size_t	dst_length;

	i = 0;
	src_length = ft_strlen(src);
	if (!(dst) && size == 0)
		return (src_length);
	dst_length = ft_strlen(dst);
	while (*dst != '\0' && dst_length < size)
		dst++;
	if (size <= dst_length || size <= 0)
		return (src_length + size);
	while (src[i] != '\0' && dst_length + i + 1 < size)
	{
		*dst = src[i];
		dst++;
		i++;
	}
	*dst = '\0';
	return (dst_length + src_length);
}

/*
#include <stdio.h>

int main()
{
	char src[100] = "bbbb";
	char dest[100] = "aaaaaaaaaaaaaaa";
	unsigned int size;

	size = 10;
	printf("%d", ft_strlcat(dest, src, size));
}
*/
