/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:50:51 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/20 08:26:33 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirection(char *cmd, int *i)
{
	int	redir;

	redir = 0;
	if (cmd[*i] == '<')
	{
		redir = INPUT;
		if (cmd[*i + 1] == '<')
		{
			redir = HEREDOC;
			*i += 1;
		}
	}
	else if (cmd[*i] == '>')
	{
		redir = OUTPUT;
		if (cmd[*i + 1] == '>')
		{
			redir = APPEND;
			*i += 1;
		}
	}
	return (redir);
}

void	error_access_redirection(t_shell *data, char *cmd, \
	t_utils *utils)
{
	while (cmd[++utils->i] && cmd[utils->i] != '&' && cmd[utils->i] != '|')
	{
		utils->result_tmp = check_redirection(cmd, &utils->i);
		if (utils->result_tmp == HEREDOC)
		{
			utils->tmp = get_filename(&cmd[utils->i], &utils->i);
			utils->fd = create_heredoc_fd(data, &utils->tmp);
			free(utils->tmp);
			close(utils->fd);
		}
	}
	if (utils->result == INPUT)
		data->cmd_group.cmd_list->infile = ft_strdup(utils->str);
	else if (utils->result == OUTPUT || utils->result == APPEND)
		data->cmd_group.cmd_list->outfile = ft_strdup(utils->str);
	free(utils->str);
}

void	get_redirection(t_shell *data, t_utils *utils)
{
	if (utils->result == INPUT || utils->result == HEREDOC)
	{
		data->cmd_group.cmd_list->fd_in = get_fd(data, utils->result, &utils->str, \
			data->cmd_group.cmd_list->fd_in);
		data->cmd_group.cmd_list->infile = ft_strdup(utils->str);
	}
	else if (utils->result == OUTPUT || utils->result == APPEND)
	{
		data->cmd_group.cmd_list->fd_out = get_fd(data, utils->result, &utils->str, \
			data->cmd_group.cmd_list->fd_out);
		data->cmd_group.cmd_list->outfile = ft_strdup(utils->str);
	}
	free(utils->str);
}

int	redirection(t_shell *data, char *cmd)
{
	t_utils	utils;

	utils.i = -1;
	utils.str = NULL;
	while (cmd[++utils.i] && cmd[utils.i] != '&' && cmd[utils.i] != '|')
	{
		utils.result_tmp = check_redirection(cmd, &utils.i);
		while (utils.result_tmp == 0 && cmd[++utils.i])
			utils.result_tmp = check_redirection(cmd, &utils.i);
		if (!cmd[utils.i])
			break ;
		utils.str = get_filename(&cmd[utils.i], &utils.i);
		utils.result = utils.result_tmp;
		if ((utils.result == INPUT && access(utils.str, F_OK | R_OK) == -1) || \
		((utils.result_tmp == OUTPUT || utils.result_tmp == APPEND) && \
		access(utils.str, F_OK) == 0 && access(utils.str, W_OK) == -1))
		{
			error_access_redirection(data, cmd, &utils);
			break ;
		}
		else
			get_redirection(data, &utils);
	}
	return (0);
}
