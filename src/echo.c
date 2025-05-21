/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:42:17 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/21 00:06:12 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_shell *data, char **strs)
{
	t_utils	utils;
	int		n;
	int		i;

	utils.start = 0;
	utils.j = 0;
	n = 0;
	while (strs[++utils.start])
	{
		i = 0;
		if (strs[utils.start][0] == '-' && utils.start == 1)
		{
			while (strs[utils.start][++i])
			{
				if (strs[utils.start][i] != 'n')
				{
					n = 1;
					break ;
				}
			}
		}
		if (strs[utils.start])
		{
			if (n == 0 && ft_strncmp(strs[utils.start], "-n", 2) == 0)
				utils.j = 1;
			else
			{
				utils.i = 0;
				ft_putstr_fd(&strs[utils.start][utils.i], 1);
				if (strs[utils.start + 1])
					ft_putstr_fd(" ", 1);
			}
		}
		n = 1;
	}
	if (!utils.j)
		ft_putstr_fd("\n", 1);
	data->exit_status = 0;
}
