/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:41:39 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/28 19:26:44 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd(char **str, t_prompt *info)
{
	int		start;
	int		end;
	int		quote;
	char	*path;

	quote = 0;
	start = 0;
	if (!str[1])
		path = ft_strdup(info->home);
	else
	{
		end = ft_strlen(str[1]);
		if (str[1][start] == '\'' || str[1][start] == '\"')
		{
			quote = str[1][start];
			start++;
		}
		while (str[1][++end] && (str[1][end] != ' ' || quote))
		{
			if (str[1][end] == quote)
				break ;
		}
		path = ft_substr(str[1], start, end - start);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishel: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free(path);
}
