/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:54:41 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/28 22:49:56 by rel-hass         ###   ########.fr       */
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
