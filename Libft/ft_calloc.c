/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:56:41 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/27 05:31:01 by rel-hass         ###   ########.fr       */
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
