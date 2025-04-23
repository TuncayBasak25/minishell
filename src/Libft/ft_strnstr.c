/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:54:41 by rel-hass          #+#    #+#             */
/*   Updated: 2024/10/17 07:54:44 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *) big);
	while (i < len && big[i] != '\0' && little[j])
	{
		while (i < len && big[i] == little[j] && little[j] != '\0')
		{
			i++;
			j++;
		}
		if (little[j] != '\0')
		{
			i = i - j + 1;
			j = 0;
		}
		else
			return ((char *) &big[i - j]);
	}
	return (0);
}
/*
#include <stdio.h>
#include<string.h>
int main()
{
	char str[100] = "Hello gkoigjriejriigrflhadjfre grr g rgrgreger";
	char to_find[100] = "grr";
	printf("%s\n", ft_strnstr(str, to_find, 5));
	printf("%s\n", strnstr(str, to_find, 5));
}
*/
