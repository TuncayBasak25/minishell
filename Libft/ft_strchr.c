/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:52:06 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:52:09 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if (*s == (unsigned char) c)
		return ((char *) s);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%s\n", ft_strchr("teste", 357));
	printf("%s\n", strchr("teste", 357));
	return (0);
}
*/