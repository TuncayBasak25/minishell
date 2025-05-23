/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:44:55 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/24 00:53:22 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var_heredoc(t_shell *data, char *line, char *delimiter)
{
	int	i;

	i = -1;
	while (delimiter[++i])
	{
		if (delimiter[i] == '\"' || delimiter[i] == '\'')
			return (line);
	}
	data->prompt_len_expanded = \
	calc_expanded_length(line, data->env, data->exit_status);
	return (expand_variables(data, line));
}

static void	read_heredoc(t_shell *data, char *delimiter, char *dnq, int pipe)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strcmp(line, dnq))
	{
		line = expand_var_heredoc(data, line, delimiter);
		ft_putendl_fd(line, pipe);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (g_sig == SIGINT)
		data->heredoc_quit = 1;
	else if (line == NULL)
		printf("minishell: warning: here-document delimited by \
end-of-file (wanted `%s')\n", dnq);
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
	dup2(save_stdin, 0);
	close(save_stdin);
	free(delimiter_no_quotes);
	close(pipe_fd[1]);
	if (!data->heredoc_quit)
		return (pipe_fd[0]);
	close(pipe_fd[0]);
	return (-1);
}
