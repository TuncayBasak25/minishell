/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:44:55 by tbasak            #+#    #+#             */
/*   Updated: 2025/06/03 21:43:54 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var_heredoc(t_shell *data, char *line, char *delimiter)
{
	int	i;

	i = -1;
	while (delimiter[++i])
	{
		if (delimiter[i] == '\"' || delimiter[i] == '\'')
			return (line);
	}
	return (expand_variables_in_heredoc(data, line));
}

static void	print_heredoc(t_shell *data, char *line, int fd, char *dnq)
{
	if (line)
		ft_putendl_fd(line, fd);
	if (!line && g_sig != SIGINT)
	{
		ft_fprintf(2, HEREDOC_WARNING, data->nb_line, dnq);
		data->heredoc_unexpected = true;
	}
	if (!line && g_sig == SIGINT)
		printf("\n");
}

static void	read_heredoc(t_shell *data, char *delimiter, char *dnq, int pipe)
{
	char	*line;

	if (data->nb_line_heredoc > 0)
		data->nb_line += data->nb_line_heredoc;
	if (data->nb_line_heredoc > 0 && !data->prev_status_is_ctrl_d)
		data->nb_line++;
	data->nb_line_heredoc = 0;
	while (true)
	{
		line = prompt_line(data, "> ");
		if (line == NULL || ft_strcmp(line, dnq) == 0)
			break ;
		line = expand_var_heredoc(data, line, delimiter);
		ft_putendl_fd(line, pipe);
		free(line);
		data->nb_line_heredoc++;
	}
	free(line);
	if (g_sig == SIGINT)
		data->heredoc_quit = 1;
	else if (!line)
	{
		data->prev_status_is_ctrl_d = true;
		print_heredoc(data, NULL, -1, dnq);
	}
}

int	create_heredoc_fd(t_shell *data, char **delimiter)
{
	int		pipe_fd[2];
	char	*delimiter_no_quotes;

	if (data->heredoc_quit || pipe(pipe_fd) == -1)
		return (-1);
	delimiter_no_quotes = strip_quotes(*delimiter);
	read_heredoc(data, *delimiter, delimiter_no_quotes, pipe_fd[1]);
	if (g_sig == SIGINT)
		printf("\n");
	if (g_sig == SIGINT && data->prev_status_is_ctrl_d == true)
		printf("\n");
	free(delimiter_no_quotes);
	close(pipe_fd[1]);
	if (!data->heredoc_quit)
		return (pipe_fd[0]);
	close(pipe_fd[0]);
	return (-1);
}
