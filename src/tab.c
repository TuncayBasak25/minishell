/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:24:10 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 08:26:54 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_inittab(int size)
{
	char	**str;

	str = (char **) ft_calloc(size + 1, sizeof(char *));
	if (!(str))
		return (NULL);
	str[size] = NULL;
	return (str);
}

void	*free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (NULL);
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	return (NULL);
}
