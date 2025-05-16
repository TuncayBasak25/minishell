/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:50:51 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/16 05:22:45 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_heredoc_fd(char **delimiter)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, *delimiter))
			break ;
		if (line)
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
		free(line);
	}
	free(line);
	close(fd);
	free(*delimiter);
	*delimiter = ft_strdup(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_RDONLY);
	return (fd);
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

void	error_access_redirection(t_cmd_group *pipeline, char *cmd, \
	t_utils *utils)
{
	while (cmd[++utils->i] && cmd[utils->i] != '&' && cmd[utils->i] != '|')
	{
		utils->result_tmp = check_redirection(cmd, &utils->i);
		if (utils->result_tmp == HEREDOC)
		{
			utils->tmp = get_filename(&cmd[utils->i], &utils->i);
			utils->fd = create_heredoc_fd(&utils->tmp);
			free(utils->tmp);
			close(utils->fd);
		}
	}
	if (utils->result == INPUT)
		pipeline->cmd_list->infile = ft_strdup(utils->str);
	else if (utils->result == OUTPUT || utils->result == APPEND)
		pipeline->cmd_list->outfile = ft_strdup(utils->str);
	free(utils->str);
}

void	get_redirection(t_cmd_group *pipeline, t_utils *utils)
{
	if (utils->result == INPUT || utils->result == HEREDOC)
	{
		pipeline->cmd_list->fd_in = get_fd(utils->result, &utils->str, \
			pipeline->cmd_list->fd_in);
		pipeline->cmd_list->infile = ft_strdup(utils->str);
	}
	else if (utils->result == OUTPUT || utils->result == APPEND)
	{
		pipeline->cmd_list->fd_out = get_fd(utils->result, &utils->str, \
			pipeline->cmd_list->fd_out);
		pipeline->cmd_list->outfile = ft_strdup(utils->str);
	}
	free(utils->str);
}

int	redirection(t_cmd_group *pipeline, char *cmd)
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
			error_access_redirection(pipeline, cmd, &utils);
			break ;
		}
		else
			get_redirection(pipeline, &utils);
	}
	return (0);
}
