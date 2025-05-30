/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:38:43 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/30 15:06:45 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cmd->custom_path)
			execve(cmd->custom_path, cmd->command, data->env);
		print_error_exec(data, cmd);
		free_shell(data, 1);
		exit(data->exit_status);
	}
}

static void	fork_and_setup_pipeline_stage(t_shell *data, t_cmd \
	*cmds, int *pipefd, int prev_fd)
{
	data->prog_status = 1;
	if (cmds->next && pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	data->pid_last = fork();
	if (data->pid_last == -1)
		exit(EXIT_FAILURE);
	if (data->pid_last == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
	signal(SIGQUIT, quit_handler);
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
	signal(SIGQUIT, SIG_IGN);
}
