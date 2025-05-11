/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:38:43 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/11 23:18:44 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	built_in(t_shell *data, t_cmd *cmds)
{
	if (!ft_strncmp(*cmds->command, "cd", 2) && \
		ft_strlen(*cmds->command) == 2)
	{
		if (cmds->prev || cmds->next)
			return (replace_command_with_echo_n(&cmds), 0);
		if (cmds->command[1])
		{
			if (cmds->command[2])
				g_sig = 1;
			if (cmds->command[2])
				return (ft_putstr_fd(WHITE"minishell: cd: too many arguments\n"\
					RESET, 2), 1);
			cmds->command[1] = normalize_cd_args(data->env, cmds->command[1]);
		}
		return (cd(data, cmds->command, &data->prompt), 1);
	}
	else if (!ft_strncmp(*cmds->command, "exit", 4) && \
		ft_strlen(*cmds->command) == 4)
	{
		if (cmds->prev || cmds->next)
			return (replace_command_with_echo_n(&cmds), 0);
		exit_minishell(data, cmds);
		return (1);
	}
	return (0);
}

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

static void	exec_cmd(t_cmd *cmd, char **envp)
{
	redir_io(cmd);
	if (!ft_strncmp(*cmd->command, "echo", 4) && \
		ft_strlen(*cmd->command) == 4)
		echo(cmd->command, envp);
	else if (!ft_strncmp(*cmd->command, "pwd", 3) && \
		ft_strlen(*cmd->command) == 3)
		pwd();
	else
	{
		if (execve(cmd->custom_path, cmd->command, envp))
		{
			ft_putstr_fd(WHITE"minishell: command not found: ", 2);
			ft_putstr_fd(*cmd->command, 2);
			ft_putstr_fd("\n"RESET, 2);
			g_sig = 127;
			exit(g_sig);
		}
	}
	exit(g_sig);
}

static void	fork_and_setup_pipeline_stage(t_cmd \
	*cmds, int *pipefd, int prev_fd, char **envp)
{
	pid_t	pid;

	if (cmds->next && pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
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
		exec_cmd(cmds, envp);
	}
	if (prev_fd != -1)
		close(prev_fd);
}

void	exec(t_shell *data, t_cmd *cmds, char **envp)
{
	int		pipefd[2];
	int		prev_fd;

	prev_fd = -1;
	while (cmds)
	{
		if (handle_missing_command_or_infile(&cmds))
			continue ;
		if (built_in(data, cmds))
		{
			cmds = cmds->next;
			continue ;
		}
		fork_and_setup_pipeline_stage(cmds, pipefd, prev_fd, envp);
		if (cmds->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmds = cmds->next;
	}
	while (wait(NULL) > 0 || errno != ECHILD)
		;
}
