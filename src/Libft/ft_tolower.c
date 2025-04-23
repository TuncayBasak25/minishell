/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:51:47 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:51:49 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

void viderBuffer(void)
{
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}

int main(void)
{
	int		choice;
	char	c;
	int		i;

	i = 0;
	printf("(1) Tester toute la table ascii\n");
	printf("(2) Tester la table ascii étendue\n");
	printf("(3) Tester un caractère au choix\n");
	printf("(4) Tester INT_MIN\n");
	printf("Choisir : ");
	scanf("%d", &choice);
	printf("\n");
	viderBuffer();
	if (choice == 3)
	{
		printf("Entrer un caractère : ");
		scanf("%c", &c);
		printf("Caractère / ft_isascii / isascii\n");
		printf("	%c = 	%c		%c\n", c, ft_tolower(c), tolower(c));
	}
	else if (choice == 1)
	{
		printf("Caractère / ft_isascii / isascii\n");
		while(i < 128)
		{
			printf("	%c = 	%c		%c\n", i, ft_tolower(i), tolower(i));
			i++;
		}
	}
	else if (choice == 2)
	{
		printf("Caractère / ft_isascii / isascii\n");
		while(i < 256)
		{
			printf("	%c = 	%c		%c\n", i, ft_tolower(i), tolower(i));
			i++;
		}
	}
	else
	{
		printf("Caractère / ft_isascii / isascii\n");
		printf("%c = %d	%d\n", INT_MIN, ft_tolower(INT_MIN), tolower(INT_MIN));
	}
	return (0);
}
*/
