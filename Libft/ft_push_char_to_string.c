/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_char_to_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 05:59:59 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 07:36:49 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_push_char_to_string(char *str, char c)
{
	size_t	len;
	char	*new_str;

	if (!str)
	{
		new_str = (char *) ft_calloc(2, sizeof(char));
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = (char *) ft_realloc(str, len + 1, len + 2);
	if (!new_str)
		return (NULL);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
