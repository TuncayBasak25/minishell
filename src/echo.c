/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:42:17 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 08:12:28 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_shell *data, char **strs)
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
	data->exit_status = 0;
}
