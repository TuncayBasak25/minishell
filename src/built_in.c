/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:20 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/12 17:39:59 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (SUCCESS);
	else if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		return (SUCCESS);
	else if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (SUCCESS);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		return (SUCCESS);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		return (SUCCESS);
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (SUCCESS);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		return (SUCCESS);
	return (FAIL);
}

void	built_in(t_shell *data, t_cmd *cmds)
{
	if (!ft_strncmp(*cmds->command, "echo", 4) && \
		ft_strlen(*cmds->command) == 4)
		echo(cmds->command);
	else if (!ft_strncmp(*cmds->command, "cd", 2) && \
		ft_strlen(*cmds->command) == 2)
		cd(data, cmds->command, &data->prompt);
	else if (!ft_strncmp(*cmds->command, "pwd", 3) && \
		ft_strlen(*cmds->command) == 3)
		pwd();
	else if (!ft_strncmp(*cmds->command, "export", 6) && \
		ft_strlen(*cmds->command) == 6)
		export(data, cmds->command[1]);
	else if (!ft_strncmp(*cmds->command, "unset", 5) && \
		ft_strlen(*cmds->command) == 5)
		unset(data, cmds->command[1]);
	else if (!ft_strncmp(*cmds->command, "env", 3) && \
		ft_strlen(*cmds->command) == 3)
		environnement(data->env, data->env_len);
	else if (!ft_strncmp(*cmds->command, "exit", 4) && \
		ft_strlen(*cmds->command) == 4)
		exit_minishell(data, cmds);
}

void	builtin_parent_process(t_shell *data, t_cmd *cmd)
{
	int	stdin_fd;
	int	stdout_fd;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	if (stdin_fd == -1 || stdout_fd == -1)
		return (perror("dup"));
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	built_in(data, cmd);
	if (cmd->fd_in > 2)
		dup2(stdin_fd, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
}
