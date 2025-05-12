/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:42:17 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/12 14:39:56 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(char **strs)
{
	t_utils	utils;

	utils.i = 0;
	utils.j = 0;
	while (strs[++utils.i])
	{
		if (ft_strncmp(strs[utils.i], "-n", 2) == 0)
			utils.j = 1;
		else
			break ;
	}
	while (strs[utils.i])
	{
		ft_putstr_fd(strs[utils.i], 1);
		if (strs[utils.i + 1])
			ft_putstr_fd(" ", 1);
		utils.i++;
	}
	if (!utils.j)
		ft_putstr_fd("\n", 1);
	g_sig = 0;
}
