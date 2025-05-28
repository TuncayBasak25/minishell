/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:44:55 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/28 19:17:00 by rel-hass         ###   ########.fr       */
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
	data->prompt_len_expanded += \
	calc_expanded_length(data, line, data->env, data->exit_status);
	return (expand_variables(data, line));
}

static void	print_heredoc(t_shell *data, char *line, int fd, char *dnq)
{
	if (line)
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	if (!line && g_sig == 0)
		printf(HEREDOC_WARNING, data->nb_line, dnq);
	if (!line && g_sig == 2)
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
	line = readline("> ");
	while (line && ft_strcmp(line, dnq))
	{
		line = expand_var_heredoc(data, line, delimiter);
		ft_putendl_fd(line, pipe);
		free(line);
		data->nb_line_heredoc++;
		line = readline("> ");
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
	int		save_stdin;
	char	*delimiter_no_quotes;

	if (data->heredoc_quit || pipe(pipe_fd) == -1)
		return (-1);
	delimiter_no_quotes = strip_quotes(*delimiter);
	save_stdin = dup(0);
	signal(SIGINT, sigint_handler);
	read_heredoc(data, *delimiter, delimiter_no_quotes, pipe_fd[1]);
	signal(SIGINT, sigint_prompt);
	if (g_sig == SIGINT)
		printf("\n");
	if (g_sig == SIGINT && data->prev_status_is_ctrl_d == true)
		printf("\n");
	dup2(save_stdin, 0);
	close(save_stdin);
	free(delimiter_no_quotes);
	close(pipe_fd[1]);
	if (!data->heredoc_quit)
		return (pipe_fd[0]);
	close(pipe_fd[0]);
	return (-1);
}
