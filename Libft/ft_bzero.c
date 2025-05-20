/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:14:06 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/16 14:14:07 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = -1;
	p = s;
	while (++i < n)
		p[i] = '\0';
}

/*
#include <stdio.h>
#include <strings.h>

void	*ft_0(void *s, size_t n)
{
	size_t	i;
	unsigned char	*p;

	i = -1;
	p = s;
	while (++i < n)
		p[i] = '0';
	return (s);
}

int	main(void)
{
	int	n;

	printf("Entrer une taille : ");
	scanf("%d", &n);
	printf("\nTaille : %d\n", n);
	printf("Ft_bzero : \"%s\"\n", (char *) ft_0(ft_calloc(n, sizeof(char)), n));
	printf("---Bzero : \"%s\"\n", (char *) ft_0(calloc(n, sizeof(char)), n));
	return (0);
}
*/
