/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_string_to_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 06:26:50 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 07:36:58 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_push_string_to_string(char *str, const char *to_add)
{
	size_t	len;
	size_t	add_len;
	char	*new_str;

	if (!to_add)
		return (str);
	add_len = ft_strlen(to_add);
	if (!str)
	{
		new_str = (char *) malloc(add_len + 1);
		if (!new_str)
			return (NULL);
		ft_memcpy(new_str, to_add, add_len + 1);
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = (char *) ft_realloc(str, len + 1, len + add_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str + len, to_add, add_len + 1);
	return (new_str);
}
