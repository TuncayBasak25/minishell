/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:08:14 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/16 12:08:23 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1024);
	else if (c == -2147483648)
		ft_isalpha(c);
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
		printf("Caractère / ft_isalpha / isalpha\n");
		printf("	%c = 	%d		%d\n", c, ft_isalpha(c), isalpha(c));
	}
	else if (choice == 1)
	{
		printf("Caractère / ft_isalpha / isalpha\n");
		while(i < 128)
		{
			printf("	%c =	 %d		%d\n", i, ft_isalpha(i), isalpha(i));
			i++;
		}
	}
	else if (choice == 2)
	{
		printf("Caractère / ft_isalpha / isalpha\n");
		while(i < 256)
		{
			printf("	%c = 	%d 		%d\n", i, ft_isalpha(i), isalpha(i));
			i++;
		}
	}
	else
	{
		printf("	%c = %d\n", INT_MIN, ft_isalpha(INT_MIN));
		//printf("	%c = %d\n", INT_MIN, isalpha(INT_MIN));
	}
	return (0);
}
*/
