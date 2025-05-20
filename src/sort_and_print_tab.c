/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:49:19 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 08:23:25 by tbasak           ###   ########.fr       */
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

static void	print_export(char **strs, int size)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < size)
	{
		if (strs[i] && strs[i][0] != '_')
		{
			ft_putstr_fd("declare -x ", 1);
			len = ft_strlen(strs[i]);
			j = -1;
			while (++j < len)
			{
				ft_putchar_fd(strs[i][j], 1);
				if (strs[i][j] == '=')
				{
					ft_putchar_fd('\"', 1);
					ft_putstr_fd(strs[i] + j + 1, 1);
					ft_putstr_fd("\"\n", 1);
					break ;
				}
			}
		}
	}
}

void	sort_and_print_tab(t_shell *data, char **tab, int size)
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
	data->exit_status = 0;
}
