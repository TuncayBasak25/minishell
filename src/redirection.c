/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:50:51 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/24 11:58:10 by rel-hass         ###   ########.fr       */
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
	while (cmd[start] && (cmd[start] == ' ' || cmd[start] == '<' || cmd[start] == '>'))
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
		while (cmd[end] && cmd[end] != ' ' && cmd[end] != '<' && cmd[end] != '>')
			end++;
	}
	*s = start;
	*e = end;
}

static void	file_redirection(int type, int *fd, char *cmd, int *i)
{
	int		start;
	int		end;
	char	*file;

	start_and_end(cmd, &start, &end);
	file = ft_substr(cmd, start, end - start);
	*i += end;
	if (!file)
		return ;
	printf("file : %s\n", file);
	if (*fd > 2)
		close(*fd);
	*fd = -1;
	if (type == INPUT_REDIREC)
		*fd = open(file, O_RDONLY);
	else if (type == OUTPUT_REDIREC)
		*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		*fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == HERDOC)
		*fd = open(file, O_RDONLY);
	free(file);
}

int	redirection(t_cmd_group *pipeline, char *cmd)
{
	int		i;
	int		redir;

	i = -1;
	printf("redirection : %s\n", cmd);
	while (cmd[++i] && cmd[i] != '&' && cmd[i] != '|')
	{
		redir = 0;
		if (cmd[i] == '<')
		{
			redir = INPUT_REDIREC;
			if (cmd[i + 1] == '<')
			{
				redir = HERDOC;
				i++;
			}
		}
		else if (cmd[i] == '>')
		{
			redir = OUTPUT_REDIREC;
			if (cmd[i + 1] == '>')
			{
				redir = APPEND;
				i++;
			}
		}
		if (!cmd[i])
			break ;
		if (redir == INPUT_REDIREC)
			file_redirection(redir, &pipeline->cmd_list->fd_in, &cmd[i], &i);
		else if (redir == HERDOC)
			file_redirection(redir, &pipeline->cmd_list->fd_in, &cmd[i], &i);
		else if (redir == OUTPUT_REDIREC || redir == APPEND)
			file_redirection(redir, &pipeline->cmd_list->fd_out, &cmd[i], &i);
	}
	return (0);
}
