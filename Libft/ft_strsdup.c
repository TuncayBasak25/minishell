/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:11:04 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 16:25:51 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsdup(char **tab)
{
	size_t	i;
	char	**new_tab;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	new_tab = (char **) malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			while (i > 0)
				free(new_tab[--i]);
			free(new_tab);
			return (NULL);
		}
	}
	new_tab[i] = NULL;
	return (new_tab);
}
