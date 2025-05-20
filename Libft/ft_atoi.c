/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:55:07 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:55:11 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	sign = 1;
	n = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n *= 10;
		n += nptr[i] - '0';
		i++;
	}
	return (n * sign);
}

/*
#include <stdio.h>

int main(void)
{
	char	s[100];

	printf("Chaîne de caractères : ");
	scanf("%s", s);
	printf("\nChaîne de caractères : \"%s\"\n", s)
	printf("Ft_atoi : %d\nAtoi : %d\n", ft_atoi(s), atoi(s));
	return (0);
}
*/
