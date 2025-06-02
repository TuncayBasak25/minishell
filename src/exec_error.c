/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 03:41:38 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/01 20:47:47 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_path_exec(t_shell *data, t_cmd *cmd)
{
	struct stat	buf;

	if ((access(cmd->custom_path, F_OK) == -1))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->custom_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status = 127;
	}
	else if (stat(cmd->custom_path, &buf) == 0)
	{
		data->exit_status = 126;
		if (S_ISDIR(buf.st_mode) == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->custom_path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->custom_path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
	}
}

void	print_error_exec(t_shell *data, t_cmd *cmd)
{
	int	slash;

	slash = find_char(*cmd->command, '/');
	if (!slash)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(*cmd->command, 2);
		ft_putstr_fd("\n", 2);
		data->exit_status = 127;
	}
	else
		print_error_path_exec(data, cmd);
}
