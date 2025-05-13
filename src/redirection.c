/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:50:51 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/13 05:32:22 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	start_and_end(char *cmd, int *s, int *e)
{
	int	start;
	int	end;
	int	quote;

	quote = 0;
	start = 0;
	while (cmd[start] && (cmd[start] == ' ' || \
		cmd[start] == '<' || cmd[start] == '>'))
		start++;
	end = start + 1;
	if (cmd[start] == '\"' || cmd[start] == '\'')
	{
		quote = cmd[start];
		start++;
		while (cmd[end] && cmd[end] != quote)
			end++;
	}
	else
	{
		while (cmd[end] && cmd[end] != ' ' && \
			cmd[end] != '<' && cmd[end] != '>')
			end++;
	}
	*s = start;
	*e = end;
}

static int	create_heredoc_fd(char **delimiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	*delimiter = ft_strdup(".heredoc_tmp");
	fd = open(".heredoc_tmp", O_RDONLY);
	return (fd);
}

static char	*file_redirection(int type, int *fd, char *cmd, int *i)
{
	int		start;
	int		end;
	char	*file;

	start_and_end(cmd, &start, &end);
	file = ft_substr(cmd, start, end - start);
	*i += end - 1;
	if (!file)
		return (NULL);
	if (*fd > 2)
		close(*fd);
	*fd = -1;
	if (type == INPUT)
		*fd = open(file, O_RDONLY);
	else if (type == OUTPUT)
		*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		*fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == HERDOC)
		*fd = create_heredoc_fd(&file);
	return (file);
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
			redir = HERDOC;
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

int	redirection(t_cmd_group *pipeline, char *cmd)
{
	int		i;
	int		redir;

	i = -1;
	while (cmd[++i] && cmd[i] != '&' && cmd[i] != '|')
	{
		redir = check_redirection(cmd, &i);
		if (!cmd[i])
			break ;
		if ((redir == INPUT || redir == HERDOC) && pipeline->cmd_list->infile)
			free(pipeline->cmd_list->infile);
		else if ((redir == OUTPUT || redir == APPEND) && \
			pipeline->cmd_list->outfile)
			free(pipeline->cmd_list->outfile);
		if (redir == INPUT)
			pipeline->cmd_list->infile = file_redirection(redir, \
				&pipeline->cmd_list->fd_in, &cmd[i], &i);
		else if (redir == HERDOC)
			pipeline->cmd_list->infile = file_redirection(redir, \
				&pipeline->cmd_list->fd_in, &cmd[i], &i);
		else if (redir == OUTPUT || redir == APPEND)
			pipeline->cmd_list->outfile = file_redirection(redir, \
				&pipeline->cmd_list->fd_out, &cmd[i], &i);
	}
	return (0);
}
