/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:55:28 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/28 16:00:37 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_u64	cstring_len(const char *cstring)
{
	t_u64	len;

	if (cstring == 0)
		return (0);
	len = 0;
	while (cstring[len] != '\0')
		len++;
	return (len);
}
