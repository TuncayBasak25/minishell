/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:52:41 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/16 12:52:43 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
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
		printf("	%c = 	%d		%d\n", c, ft_isascii(c), isascii(c));
	}
	else if (choice == 1)
	{
		printf("Caractère / ft_isascii / isascii\n");
		while(i < 128)
		{
			printf("	%c = 	%d		%d\n", i, ft_isascii(i), isascii(i));
			i++;
		}
	}
	else if (choice == 2)
	{
		printf("Caractère / ft_isascii / isascii\n");
		while(i < 256)
		{
			printf("	%c = 	%d		%d\n", i, ft_isascii(i), isascii(i));
			i++;
		}
	}
	else
	{
		printf("Caractère / ft_isascii / isascii\n");
		printf("%c = %d	%d\n", INT_MIN, ft_isascii(INT_MIN), isascii(INT_MIN));
	}
	return (0);
}
*/
