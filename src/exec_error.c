/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 03:41:38 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/31 06:45:43 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_path_exec(t_shell *data, t_cmd *cmd)
{
	struct stat	buf;

	if ((access(cmd->custom_path, F_OK) == -1))
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", \
			cmd->custom_path);
		data->exit_status = 127;
	}
	else if (stat(cmd->custom_path, &buf) == 0)
	{
		data->exit_status = 126;
		if (S_ISDIR(buf.st_mode) == 1)
			ft_fprintf(2, "minishell: %s: Is a directory\n", cmd->custom_path);
		else
			ft_fprintf(2, "minishell: %s: Permission denied\n", \
				cmd->custom_path);
	}
}

void	print_error_exec(t_shell *data, t_cmd *cmd)
{
	int	slash;

	slash = find_char(*cmd->command, '/');
	if (!slash)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", *cmd->command);
		data->exit_status = 127;
	}
	else
		print_error_path_exec(data, cmd);
}
