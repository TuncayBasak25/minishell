/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:44:55 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/24 10:18:50 by rel-hass         ###   ########.fr       */
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
	data->prompt_len_expanded += \
	calc_expanded_length(data, line, data->env, data->exit_status);
	return (expand_variables(data, line));
}

void	print_heredoc(char *line, int fd, char *dnq)
{
	if (line)
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	if (!line && g_sig == 0)
		printf("minishell: warning: here-document delimited by \
end-of-file (wanted `%s')\n", dnq);
	if (!line && g_sig == 2)
		printf("\n");
}

static void	child_handler(t_shell *data, char *delimiter, int fd, char *dnq)
{
	char	*line;
	int		status;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, dnq))
		{
			if (!line)
				print_heredoc(line, fd, dnq);
			break ;
		}
		line = expand_var_heredoc(data, line, delimiter);
		print_heredoc(line, fd, dnq);
		free(line);
	}
	free(line);
	status = 0;
	if (g_sig)
		status = 1;
	close(fd);
	free_shell(data, 1);
	exit(status);
}

static int	read_heredoc(t_shell *data, char *delimiter, char *dnq)
{
	int	pipe_fd[2];
	int	pid;
	int	status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		child_handler(data, delimiter, pipe_fd[1], dnq);
	}
	close(pipe_fd[1]);
	status = 1;
	while (waitpid(pid, &status, 0) == -1)
		continue ;
	if (status == 0)
		return (pipe_fd[0]);
	close(pipe_fd[0]);
	data->heredoc_quit = 1;
	return (-1);
}

int	create_heredoc_fd(t_shell *data, char **delimiter)
{
	int		fd;
	char	*delimiter_no_quotes;

	if (data->heredoc_quit)
		return (-1);
	delimiter_no_quotes = strip_quotes(*delimiter);
	fd = read_heredoc(data, *delimiter, delimiter_no_quotes);
	free(delimiter_no_quotes);
	return (fd);
}
