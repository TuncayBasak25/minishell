/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:20 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/03 11:30:33 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || \
	ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || \
	ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || \
	ft_strcmp(cmd, "exit") == 0);
}

void	built_in(t_shell *data, t_cmd *cmds, int fd_in, int fd_out)
{
	if (!cmds->command)
		return ;
	if (ft_strcmp(*cmds->command, "echo") == 0)
		echo(data, cmds->command);
	else if (ft_strcmp(*cmds->command, "cd") == 0)
		cd(data, cmds->command, &data->prompt);
	else if (ft_strcmp(*cmds->command, "pwd") == 0)
		pwd(data, cmds->command);
	else if (ft_strcmp(*cmds->command, "export") == 0)
		export(data, &cmds->command[1]);
	else if (ft_strcmp(*cmds->command, "unset") == 0)
		unset(data, &cmds->command[1]);
	else if (ft_strcmp(*cmds->command, "env") == 0)
		environnement(data, cmds->command, data->env, data->env_len);
	else if (ft_strcmp(*cmds->command, "exit") == 0)
		exit_minishell(data, cmds, fd_in, fd_out);
}

void	restore_std_fds(int stdin_fd, int stdout_fd)
{
	if (stdin_fd > -1)
	{
		dup2(stdin_fd, STDIN_FILENO);
		if (stdin_fd > 2)
			close(stdin_fd);
	}
	if (stdout_fd > -1)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		if (stdout_fd > 2)
			close(stdout_fd);
	}
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
	if (cmd->command && !ft_strncmp(*cmd->command, "exit", 4) && \
	ft_strlen(*cmd->command) == 4)
		printf("exit\n");
	built_in(data, cmd, stdin_fd, stdout_fd);
	restore_std_fds(stdin_fd, stdout_fd);
}
