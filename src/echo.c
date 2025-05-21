/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:42:17 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/21 17:10:13 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_n(char **strs)
{
	int	i;

	i = 0;
	if (!strs || !*strs || !strs[1])
		return (0);
	if (strs[1][0] == '-')
	{
		while (strs[1][++i])
		{
			if (strs[1][i] != 'n')
				return (1);
		}
	}
	return (0);
}

void	echo(t_shell *data, char **strs)
{
	t_utils	utils;
	int		n;

	utils.start = 0;
	utils.j = 0;
	n = check_echo_n(strs);
	if (strs && *strs)
	{
		while (strs[++utils.start])
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
			n = 1;
		}
	}
	if (!utils.j)
		ft_putstr_fd("\n", 1);
	data->exit_status = 0;
}
