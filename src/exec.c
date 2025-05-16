/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:38:43 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/16 13:10:47 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	redir_io(t_cmd *cmd)
{
	if (cmd->fd_in >= 0 && cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0 && cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

static void	print_error_exec(t_shell *data, t_cmd *cmd)
{
	int	slash;

	slash = find_char(cmd->custom_path, '/');
	if (access(cmd->custom_path, F_OK) == -1 || \
	(access(cmd->custom_path, F_OK) == 0 && !slash))
	{
		ft_putstr_fd(WHITE"minishell: command not found: ", 2);
		ft_putstr_fd(*cmd->command, 2);
		ft_putstr_fd("\n"RESET, 2);
		data->exit_status = 127;
	}
	else
	{
		ft_putstr_fd(WHITE"minishell: ", 2);
		ft_putstr_fd(cmd->custom_path, 2);
		ft_putstr_fd(": Permission denied\n"RESET, 2);
		data->exit_status = 126;
	}
}

static void	exec_cmd(t_shell *data, t_cmd *cmd)
{
	redir_io(cmd);
	if (!cmd->command || !is_builtin(cmd->command[0]))
	{
		built_in(data, cmd, -1, -1);
		free_shell(data, 1);
		exit(data->exit_status);
	}
	else
	{
		execve(cmd->custom_path, cmd->command, data->env);
		print_error_exec(data, cmd);
		free_shell(data, 1);
		exit(data->exit_status);
	}
}

static void	fork_and_setup_pipeline_stage(t_shell *data, t_cmd \
	*cmds, int *pipefd, int prev_fd)
{
	if (cmds->next && pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	data->pid_last = fork();
	if (data->pid_last == -1)
		exit(EXIT_FAILURE);
	if (data->pid_last == 0)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
		}
		if (cmds->next)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		exec_cmd(data, cmds);
	}
	if (prev_fd != -1)
		close(prev_fd);
}

void	exec(t_shell *data, t_cmd *cmds)
{
	int		pipefd[2];
	int		prev_fd;

	prev_fd = -1;
	while (cmds)
	{
		if (handle_infile(data, &cmds) || handle_outfile(data, &cmds))
			continue ;
		if (!cmds->prev && !cmds->next && (!cmds->command || \
			!is_builtin(cmds->command[0])))
		{
			builtin_parent_process(data, cmds);
			cmds = cmds->next;
			continue ;
		}
		fork_and_setup_pipeline_stage(data, cmds, pipefd, prev_fd);
		if (cmds->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmds = cmds->next;
	}
	wait_exec(data);
}
