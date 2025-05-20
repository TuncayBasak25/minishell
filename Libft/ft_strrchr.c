/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:52:45 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:52:47 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = (int) ft_strlen(s);
	if ((unsigned char) c == '\0')
		return ((char *) &s[i]);
	while (--i >= 0)
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	//printf("%s\n", ft_strrchr("teste", 357));
	printf("%s\n", strrchr("teste", 357));
	return (0);
}
*/