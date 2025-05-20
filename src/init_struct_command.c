/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:19:54 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 08:26:05 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_struct_cmd(t_cmd *prev, char **command, char *line, char **env)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->id = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->line_cmd = line;
	cmd->command = command;
	if (cmd->command && find_char(cmd->command[0], '/'))
		cmd->custom_path = ft_strdup(cmd->command[0]);
	else if (cmd->command)
		cmd->custom_path = find_custom_path(command[0], env);
	cmd->next = NULL;
	cmd->prev = prev;
	if (cmd->prev)
		cmd->prev->next = cmd;
	return (cmd);
}
