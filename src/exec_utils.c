/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:00:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/06/03 18:33:43 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_file(char *filename, int flag, int type)
{
	if (!filename)
		return ;
	if (*filename && type)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (!*filename || (access(filename, F_OK) == -1))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(filename, flag) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	handle_outfile(t_shell *data, t_cmd **cmds)
{
	struct stat	buf;

	if ((*cmds)->outfile && ((!stat((*cmds)->outfile, &buf) && \
	S_ISDIR(buf.st_mode)) || access((*cmds)->outfile, F_OK | W_OK) == -1))
	{
		print_error_file((*cmds)->outfile, W_OK, S_ISDIR(buf.st_mode));
		if (!(*cmds)->prev || (*cmds)->command)
			data->exit_status = 1;
		else if ((*cmds)->prev && !(*cmds)->command)
		{
			data->exit_status = 1;
			return (SUCCESS);
		}
		if ((*cmds)->next || ((*cmds)->prev && !(*cmds)->next))
		{
			data->exit_status = 1;
			(*cmds)->command = free_tab((*cmds)->command);
			return (SUCCESS);
		}
		*cmds = (*cmds)->next;
		return (FAIL);
	}
	else if ((*cmds)->outfile)
		data->exit_status = 0;
	return (SUCCESS);
}

int	handle_infile(t_shell *data, t_cmd **cmds)
{
	if (!data->cmd_group.cmd_list->heredoc && (*cmds)->infile && \
	access((*cmds)->infile, F_OK | R_OK) == -1)
	{
		print_error_file((*cmds)->infile, R_OK, 0);
		if (!(*cmds)->prev || (*cmds)->command)
			data->exit_status = 1;
		else if ((*cmds)->prev && !(*cmds)->command)
		{
			data->exit_status = 0;
			return (SUCCESS);
		}
		if ((*cmds)->next || ((*cmds)->prev && !(*cmds)->next))
		{
			data->exit_status = 1;
			(*cmds)->command = free_tab((*cmds)->command);
			return (SUCCESS);
		}
		*cmds = (*cmds)->next;
		return (FAIL);
	}
	else if ((*cmds)->infile)
		data->exit_status = 0;
	return (SUCCESS);
}

int	extract_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	wait_exec(t_shell *data)
{
	data->pid_wait = waitpid(-1, &data->status, 0);
	while (data->pid_wait > 0)
	{
		if (data->pid_wait == data->pid_last)
		{
			data->exit_status = extract_exit_code(data->status);
			handle_sigquit_message(data->status, data->pid_wait, \
				data->pid_last);
		}
		data->pid_wait = waitpid(-1, &data->status, 0);
	}
	if (g_sig == SIGINT)
		write(1, "\n", 1);
}
