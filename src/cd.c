/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:41:39 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 09:09:33 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd(char **str, t_prompt *info)
{
	t_utils	utils;

	utils.quote = 0;
	utils.start = 0;
	if (!str[1])
		utils.path = ft_strdup(info->home);
	else
	{
		utils.end = ft_strlen(str[1]);
		if (str[1][utils.start] == '\'' || str[1][utils.start] == '\"')
			utils.quote = str[1][utils.start++];
		while (str[1][++utils.end] && (str[1][utils.end] != ' ' || utils.quote))
		{
			if (str[1][utils.end] == utils.quote)
				break ;
		}
		utils.path = ft_substr(str[1], utils.start, utils.end - utils.start);
	}
	if (chdir(utils.path) == -1)
	{
		ft_putstr_fd("minishel: cd: ", 2);
		ft_putstr_fd(utils.path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free(utils.path);
}
