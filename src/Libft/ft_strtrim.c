/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:45:15 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/21 10:45:16 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;

	if (!(s1))
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (s1[--size] && ft_strrchr(set, s1[size]))
		;
	return (ft_substr(s1, 0, size + 1));
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
	int		choice;
	char	s[2000];
	char	set[2000];
	char	*d;
	char	*tfixe1 = "   xxx   xxx";
	char	*tfixe2 = " x";

	printf("(1) Test dynamique\n");
	printf("(2) Test fixe\n");
	printf("Choisir : ");
	scanf("%d", &choice);
	printf("\n");
	viderBuffer();
	if (choice == 1)
	{
		printf("Entrer une chaine de caractère : ");
		scanf("%s", s);
		viderBuffer();
		printf("Caractere a retirer : ");
		scanf("%s", set);
		viderBuffer();
		d = ft_strtrim((const char *) s, set);
		printf("\nSource : %s\nCopie : \"%s\"\n", s, d);
	}
	else
	{
		d = ft_strtrim((const char *) tfixe1, tfixe2);
		printf("\nS1 : %s\nS2 : %s\nCopie : \"%s\"\n", tfixe1, tfixe2, d);
	}

	free(d);
	return (0);
}
*/
