/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 05:18:43 by rel-hass          #+#    #+#             */
/*   Updated: 2025/05/25 19:05:57 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_redir_quotes(char *cmd, int *start, int *end)
{
	int	quote;

	quote = 0;
	while (cmd[*start] == '\"' || cmd[*start] == '\'')
	{
		quote = cmd[*start];
		while (cmd[++*end] && cmd[*end] != quote)
			continue ;
		*end += 1;
		*start = *end;
	}
}

void	start_and_end(char *cmd, int *s, int *e)
{
	int	start;
	int	end;

	start = 0;
	while (cmd[start] && (is_whitespace(cmd[start]) || \
		cmd[start] == '<' || cmd[start] == '>'))
		start++;
	*s = start;
	end = start;
	if (cmd[start] == '\"' || cmd[start] == '\'')
		skip_redir_quotes(cmd, &start, &end);
	else
	{
		while (cmd[++end] && !is_whitespace(cmd[end]) && \
			cmd[end] != '<' && cmd[end] != '>')
			continue ;
	}
	*e = end;
}

char	*get_filename(char *cmd, int *i)
{
	int		start;
	int		end;
	char	*file;

	start_and_end(cmd, &start, &end);
	file = ft_substr(cmd, start, end - start);
	*i += end - 1;
	if (!file)
		return (NULL);
	return (file);
}

int	get_fd(t_shell *data, int type, char **file, int fd)
{
	if (fd > 2)
		close(fd);
	fd = -1;
	if (type == INPUT)
		fd = open(*file, O_RDONLY);
	else if (type == OUTPUT)
		fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(*file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == HEREDOC)
		fd = create_heredoc_fd(data, file);
	return (fd);
}
