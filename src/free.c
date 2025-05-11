/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:59:02 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/11 18:24:40 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	close_fd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (cmd->fd_pipe[0] > 2)
		close(cmd->fd_pipe[0]);
	if (cmd->fd_pipe[1] > 2)
		close(cmd->fd_pipe[1]);
}

static void	free_cmd(t_cmd_group *cmd_group)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = cmd_group->cmd_list;
	while (current && current->prev)
		current = current->prev;
	cmd_group->count = 0;
	cmd_group->path = free_tab(cmd_group->path);
	while (current)
	{
		close_fd(current);
		free(current->infile);
		free(current->outfile);
		free(current->line_cmd);
		free_tab(current->command);
		free(current->custom_path);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	cmd_group->cmd_list = NULL;
}

static void	free_prompt(t_prompt *prompt)
{
	free(prompt->home);
	free(prompt->user);
	free(prompt->host);
	free(prompt->pwd);
	free(prompt->full_pwd);
	free(prompt->prompt);
	free(prompt->user_input.chars);
}

void	free_shell(t_shell *data, int exit_prog)
{
	if (data->env && exit_prog)
	{
		data->env = free_tab(data->env);
		rl_clear_history();
	}
	free_cmd(&data->cmd_group);
	free_prompt(&data->prompt);
	data->prompt = (t_prompt){0};
}
