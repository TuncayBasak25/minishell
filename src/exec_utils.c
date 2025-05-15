/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:00:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/15 16:50:29 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error_file(char *filename)
{
	if ((access(filename, F_OK) == -1))
	{
		ft_putstr_fd(WHITE"minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n"RESET, 2);
	}
	else if (access(filename, R_OK) == -1)
	{
		ft_putstr_fd(WHITE"minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n"RESET, 2);
	}
}

int	handle_missing_file(t_cmd **cmds)
{
	if (((*cmds)->infile && access((*cmds)->infile, F_OK | R_OK) == -1))
	{
		print_error_file((*cmds)->infile);
		if (!(*cmds)->prev || (*cmds)->command)
			g_sig = 1;
		else if ((*cmds)->prev && !(*cmds)->command)
		{
			g_sig = 0;
			return (SUCCESS);
		}
		if ((*cmds)->next || ((*cmds)->prev && !(*cmds)->next))
		{
			g_sig = 1;
			(*cmds)->command = free_tab((*cmds)->command);
			return (SUCCESS);
		}
		*cmds = (*cmds)->next;
		return (FAIL);
	}
	else
		g_sig = 0;
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
			g_sig = extract_exit_code(data->status);
		data->pid_wait = waitpid(-1, &data->status, 0);
	}
}
