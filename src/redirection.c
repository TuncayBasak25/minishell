/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:50:51 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/23 08:11:50 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(t_utils *utils, char *cmd)
{
	if (cmd[utils->i] == '\'' || cmd[utils->i] == '\"')
	{
		utils->quote = cmd[utils->i];
		while (cmd[++utils->i] && cmd[utils->i] != utils->quote)
			continue ;
		utils->quote = 0;
	}
}

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
	if (utils->result == INPUT)
		data->cmd_group.cmd_list->heredoc = false;
	while (cmd[++utils->i] && cmd[utils->i] != '&' && cmd[utils->i] != '|')
	{
		skip_quotes(utils, cmd);
		utils->result_tmp = check_redirection(cmd, &utils->i);
		if (utils->result_tmp == HEREDOC)
		{
			utils->tmp = get_filename(&cmd[utils->i], &utils->i);
			utils->fd = create_heredoc_fd(data, &utils->tmp);
			free(utils->tmp);
			close(utils->fd);
			if (data->heredoc_quit)
				break ;
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
	if (utils->result == INPUT)
		data->cmd_group.cmd_list->heredoc = false;
	else if (utils->result == HEREDOC)
		data->cmd_group.cmd_list->heredoc = true;
	if (utils->result == INPUT || utils->result == HEREDOC)
	{
		data->cmd_group.cmd_list->fd_in = get_fd(data, utils->result, \
			&utils->str, data->cmd_group.cmd_list->fd_in);
		if (data->heredoc_quit == 0)
			data->cmd_group.cmd_list->infile = ft_strdup(utils->str);
	}
	else if (utils->result == OUTPUT || utils->result == APPEND)
	{
		data->cmd_group.cmd_list->fd_out = get_fd(data, utils->result, \
			&utils->str, data->cmd_group.cmd_list->fd_out);
		data->cmd_group.cmd_list->outfile = ft_strdup(utils->str);
	}
	if (data->heredoc_quit == 0)
	{
		free(data->cmd_group.cmd_list->infile);
		data->cmd_group.cmd_list->infile = NULL;
	}
	free(utils->str);
}

int	redirection(t_shell *data, char *cmd)
{
	t_utils	utils;

	utils.i = -1;
	while (cmd[++utils.i] && cmd[utils.i] != '&' && cmd[utils.i] != '|')
	{
		skip_quotes(&utils, cmd);
		if (!cmd[utils.i])
			break ;
		utils.result_tmp = check_redirection(cmd, &utils.i);
		if (utils.result_tmp == 0)
			continue ;
		utils.str = get_filename(&cmd[utils.i], &utils.i);
		utils.result = utils.result_tmp;
		remove_quotes(&utils.str, utils.result);
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
