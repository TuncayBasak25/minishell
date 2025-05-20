/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:53:13 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:53:18 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned const char	*p1;
	unsigned const char	*p2;

	i = 0;
	p1 = (unsigned const char *) s1;
	p2 = (unsigned const char *) s2;
	while (i < n && (p1[i] != '\0' || p2[i] != '\0'))
	{
		if ((p1[i] > p2[i]) || (p1[i] < p2[i]))
			return (p1[i] - p2[i]);
		else
			i++;
	}
	return (0);
}

/*
#include <stdio.h>

int main() {

    char login[40];
    char password[40];
	unsigned int i;

	i = 0;
    printf( "Please, enter your login: " );
    scanf( "%s", login );

    printf( "Enter your password: " );
    scanf( "%s", password );

	printf("\n\nValeur de retour : %d.\n", ft_strncmp(login, password, i));

    return 0;
}
*/
