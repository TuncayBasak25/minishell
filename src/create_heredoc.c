/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:44:55 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/20 00:46:09 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sigid)
{
	g_sig = sigid;
	rl_replace_line("", 0);
	close(0);
}

char	*expand_var_heredoc(t_shell *data, char *line, char *delimiter)
{
	int	i;

	i = -1;
	while (delimiter[++i])
	{
		if (delimiter[i] == '\"' || delimiter[i] == '\'')
			return (line);
	}
	return (expand_variables(data, line, data->env_len));
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
			break ;
		line = expand_var_heredoc(data, line, delimiter);
		if (line)
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
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
	return (-1);
}

int	create_heredoc_fd(t_shell *data, char **delimiter)
{
	int		fd;
	char	*delimiter_no_quotes;

	delimiter_no_quotes = strip_quotes(*delimiter);
	fd = read_heredoc(data, *delimiter, delimiter_no_quotes);
	free(delimiter_no_quotes);
	return (fd);
}
