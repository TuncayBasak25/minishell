/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:53:13 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/25 22:28:33 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned const char	*p1;
	unsigned const char	*p2;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	p1 = (unsigned const char *) s1;
	p2 = (unsigned const char *) s2;
	while (i < n)
	{
		if (p1[i] != p2[i] || p1[i] == '\0' || p2[i] == '\0')
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
