/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:00:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/08 13:03:11 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_command_with_echo_n(t_cmd **cmds)
{
	if ((*cmds)->command)
		free_tab((*cmds)->command);
	(*cmds)->command = malloc(sizeof(char *) * 3);
	(*cmds)[0].command[0] = ft_strdup("echo");
	(*cmds)[0].command[1] = ft_strdup("-n");
	(*cmds)[0].command[2] = NULL;
}

int	handle_missing_command_or_infile(t_cmd **cmds)
{
	if (!(*cmds)->command || ((*cmds)->infile && \
		access((*cmds)->infile, F_OK) == -1))
	{
		if ((*cmds)->infile)
		{
			if (access((*cmds)->infile, F_OK) == -1)
			{
				ft_putstr_fd(WHITE"minishell: ", 2);
				ft_putstr_fd((*cmds)->infile, 2);
				ft_putstr_fd(": No such file or directory\n"RESET, 2);
			}
			replace_command_with_echo_n(cmds);
		}
		if (!(*cmds)->command)
		{
			*cmds = (*cmds)->next;
			return (1);
		}
	}
	return (0);
}
