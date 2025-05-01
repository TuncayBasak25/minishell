/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:38:43 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/01 10:32:20 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	simple_command(t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
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
}

void	exec(t_shell *data)
{
	printf(BRED"PIPE %d : %s\n"RESET, data->cmd_group.cmd_list->id, \
		data->cmd_group.cmd_list->command[0]);
	if (!ft_strncmp(*data->cmd_group.cmd_list->command, "cd", 2) && \
		ft_strlen(*data->cmd_group.cmd_list->command) == 2)
		cd(data->cmd_group.cmd_list->command, &data->prompt);
	else if (!ft_strncmp(*data->cmd_group.cmd_list->command, "echo", 4) && \
		ft_strlen(*data->cmd_group.cmd_list->command) == 4)
		echo(data->cmd_group.cmd_list->command, data->env);
	else if (!ft_strncmp(*data->cmd_group.cmd_list->command, "pwd", 3) && \
		ft_strlen(*data->cmd_group.cmd_list->command) == 3)
		pwd();
	else if (!ft_strncmp(*data->cmd_group.cmd_list->command, "exit", 4) && \
		ft_strlen(*data->cmd_group.cmd_list->command) == 4)
	{
		printf(BRED"exit\n"RESET);
		free(data->prompt.user_input.chars);
		exit(EXIT_SUCCESS);
	}
	else
		simple_command(data->cmd_group.cmd_list, data->env);
	data->cmd_group.cmd_list = data->cmd_group.cmd_list->next;
}
