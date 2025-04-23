/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:24:10 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/20 15:25:10 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

__attribute__((cold)) char	**ft_inittab(int size)
{
	char	**str;

	str = (char **) ft_calloc(size + 1, sizeof(char *));
	if (!(str))
		return (NULL);
	str[size] = NULL;
	return (str);
}

__attribute__((cold)) void	*free_tab(char **tab)
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
