/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:38:43 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/25 23:02:12 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

__attribute__((hot)) RESULT	simple_command(t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FAIL);
	if (pid == 0)
	{
		if (execve(cmd->custom_path, cmd->command, env) == -1)
		{
			ft_putstr_fd(WHITE"minishell: command not found: ", 2);
			ft_putstr_fd(*cmd->command, 2);
			ft_putstr_fd("\n"RESET, 2);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
	return (SUCCESS);
}
