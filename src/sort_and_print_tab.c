/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:49:19 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/13 00:01:05 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**alias_ptr_tab(char **tab, int size)
{
	int		i;
	char	**tmp;

	i = -1;
	if (!tab || size <= 0)
		return (NULL);
	tmp = malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (NULL);
	while (++i < size)
		tmp[i] = tab[i];
	tmp[i] = NULL;
	return (tmp);
}

static void	print_export(char **strs, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (strs[i] && strs[i][0] != '_')
			printf("declare -x %s\n", strs[i]);
	}
}

void	sort_and_print_tab(char **tab, int size)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	if (!tab || size <= 0)
		return ;
	tmp = alias_ptr_tab(tab, size);
	if (!tmp)
		return ;
	while (++i < size)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_strcmp(tmp[j], tmp[j + 1]) > 0)
			{
				ft_swap(&tmp[j], &tmp[j + 1]);
			}
		}
	}
	print_export(tmp, size);
	free(tmp);
}
