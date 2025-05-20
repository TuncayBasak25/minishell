/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:56:41 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:56:42 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb > SIZE_MAX / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	p = malloc(size * nmemb);
	if (!(p))
		return (NULL);
	ft_bzero(p, size * nmemb);
	return (p);
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
	printf("Ft_calloc : \"%s\"\n", (char *) ft_0(ft_calloc(n, sizeof(char)), n));
	printf("---Calloc : \"%s\"\n", (char *) ft_0(calloc(n, sizeof(char)), n));
	return (0);
}
*/
