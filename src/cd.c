/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:41:39 by rel-hass          #+#    #+#             */
/*   Updated: 2025/03/30 21:01:01 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd(char *str, t_prompt *info)
{
	int		start;
	int		end;
	int		quote;
	char	*path;

	start = 2;
	quote = 0;
	while (str[start] && str[start] == ' ')
		start++;
	if (str[start] == '\0')
		path = ft_strdup(info->home);
	else
	{
		while (str[start] && str[start] == ' ')
			start++;
		end = start;
		if (str[start] == '\'' || str[start] == '\"')
		{
			quote = str[start];
			start++;
		}
		while (str[++end] && (str[end] != ' ' || quote))
		{
			if (str[end] == quote)
				break ;
		}
		path = ft_substr(str, start, end - start);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishel: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free(path);
}
