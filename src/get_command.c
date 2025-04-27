/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:14:10 by rel-hass          #+#    #+#             */
/*   Updated: 2025/04/27 14:49:24 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static const char	*skip_redir(const char *s)
{
	char	op;
	char	q;

	op = *s++;
	if (*s == op)
		s++;
	while (*s == ' ')
		s++;
	if (*s == '\'' || *s == '"')
	{
		q = *s++;
		while (*s && *s != q)
			s++;
		if (*s == q)
			s++;
	}
	else
	{
		while (*s && *s != ' ' && *s != '<' && *s != '>')
			s++;
	}
	return (s);
}

static char	*trim_spaces(char *str)
{
	char	*start;
	char	*end;

	start = str;
	while (*start == ' ')
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && *end == ' ')
		*end-- = '\0';
	return (ft_strdup(start));
}

char	*get_command(char *input)
{
	const char	*ptr;
	char		*buf;
	size_t		idx;
	bool		sq;
	bool		dq;

	ptr = input;
	buf = malloc(ft_strlen(input) + 1);
	if (!buf)
		return (NULL);
	idx = 0;
	sq = false;
	dq = false;
	while (*ptr)
	{
		if (*ptr == '\'' && !dq)
			sq = !sq;
		else if (*ptr == '"' && !sq)
			dq = !dq;
		if (!sq && !dq && (*ptr == '<' || *ptr == '>'))
		{
			ptr = skip_redir(ptr);
			continue ;
		}
		buf[idx++] = *ptr++;
	}
	buf[idx] = '\0';
	ptr = trim_spaces(buf);
	free(buf);
	return ((char *)ptr);
}

t_cmd	*init_struct_cmd(t_cmd *prev, char **command, char *line, char **env)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->id = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->fd_pipe[0] = -1;
	cmd->fd_pipe[1] = -1;
	cmd->line_cmd = line;
	cmd->command = command;
	cmd->custom_path = find_custom_path(command[0], env);
	cmd->next = NULL;
	cmd->prev = prev;
	if (cmd->prev)
		cmd->prev->next = cmd;
	return (cmd);
}

void	remove_first_quote(char **tab)
{
	char	*s;
	char	*pos;
	char	*pos2;
	char	quote;

	while (*tab)
	{
		s = *tab;
		pos = ft_strchr(s, '\'');
		pos2 = ft_strchr(s, '"');
		if (!pos || (pos2 && pos2 < pos))
			pos = pos2;
		if (!pos)
		{
			tab++;
			continue ;
		}
		quote = *pos;
		ft_memmove(pos, pos + 1, ft_strlen(pos));
		pos = ft_strchr(pos, quote);
		if (pos)
			ft_memmove(pos, pos + 1, ft_strlen(pos));
		tab++;
	}
}

RESULT	get_all_command(t_shell *data)
{
	int		i;
	char	**pipe;
	char	*line;
	char	**cmd;
	t_cmd	*prev;

	i = -1;
	pipe = split_limited(data->prompt.user_input.chars, '|', "\'\"");
	data->cmd_group.cmd_list = NULL;
	prev = NULL;
	if (!pipe)
		return (FAIL);
	data->cmd_group.path = find_path(data->env);
	while (pipe[++i])
	{
		line = get_command(pipe[i]);
		if (!line)
		{
			pipe = free_tab(pipe);
			return (FAIL);
		}
		cmd = split_space_limited(line, ' ', "\'\"");
		if (!cmd)
		{
			free(line);
			pipe = free_tab(pipe);
			return (FAIL);
		}
		remove_first_quote(cmd);
		data->cmd_group.cmd_list = init_struct_cmd(prev, \
			cmd, line, data->cmd_group.path);
		data->cmd_group.cmd_list->id = i + 1;
		(void) redirection(&data->cmd_group, pipe[i]);
		prev = data->cmd_group.cmd_list;
		int j = -1;
		while (data->cmd_group.cmd_list->command[++j])
			printf("command : %s\n", data->cmd_group.cmd_list->command[j]);
	}
	pipe = free_tab(pipe);
	return (SUCCESS);
}
