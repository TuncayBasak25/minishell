/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:49:19 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/26 12:09:59 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_print_path(t_shell *data, char *str)
{
	return (data->secret_path == false || ft_strncmp(str, "PATH=", 5));
}

void	sort_and_print_tab(t_shell *data, char **tab, int size, \
	void (*print)(t_shell *, char **, int))
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
	print(data, tmp, size);
	free(tmp);
	data->exit_status = 0;
}
