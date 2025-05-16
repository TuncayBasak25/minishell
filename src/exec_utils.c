/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:00:35 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/16 04:56:24 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error_file(char *filename, int flag)
{
	if ((access(filename, F_OK) == -1))
	{
		ft_putstr_fd(WHITE"minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n"RESET, 2);
	}
	else if (access(filename, flag) == -1)
	{
		ft_putstr_fd(WHITE"minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n"RESET, 2);
	}
}

int	handle_outfile(t_cmd **cmds)
{
	if (((*cmds)->outfile && access((*cmds)->outfile, F_OK | W_OK) == -1))
	{
		print_error_file((*cmds)->outfile, W_OK);
		if (!(*cmds)->prev || (*cmds)->command)
			g_sig = 1;
		else if ((*cmds)->prev && !(*cmds)->command)
		{
			g_sig = 1;
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
	else if ((*cmds)->outfile)
		g_sig = 0;
	return (SUCCESS);
}

int	handle_infile(t_cmd **cmds)
{
	if (((*cmds)->infile && access((*cmds)->infile, F_OK | R_OK) == -1))
	{
		print_error_file((*cmds)->infile, R_OK);
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
	else if ((*cmds)->infile)
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
