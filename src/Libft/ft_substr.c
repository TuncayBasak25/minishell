/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:09:56 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/21 09:09:57 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*dest;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_calloc(1, sizeof(char)));
	else if (len > size - start)
		len = size - start;
	dest = (char *) ft_calloc(len + 1, sizeof(char));
	if (!(dest))
		return (NULL);
	len = ft_strlcpy(dest, &s[start], len + 1);
	return (dest);
}

/*
#include <stdio.h>

void viderBuffer(void)
{
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}

int main(void)
{
	unsigned int	start;
	size_t			max;
	char			s[2000];
	char			*d;

	start = 0;
	max = 0;
	printf("Entrer une chaine de caractère : ");
	scanf("%s", s);
	viderBuffer();
	printf("\nIndice de début de copie : ");
	scanf("%d", &start);
	viderBuffer();
	printf("Indice de fin de copie : ");
	scanf("%ld", &max);
	viderBuffer();
	d = ft_substr(s, start, max);
	printf("\nSource : %s\nCopie : \"%s\"\n", s, d);
	free(d);
	return (0);
}
*/
