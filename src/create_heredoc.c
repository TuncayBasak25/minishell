/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:44:55 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/17 14:19:32 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
sigint_handler(int sigid)
{
	g_sig = sigid;
	rl_replace_line("", 0);
	close(0);
}

static void
child_handler(t_shell *data, char *delimiter, int fd)
{
	char	*line;
	int		status;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
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

static int
read_heredoc(t_shell *data, char *delimiter)
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
		child_handler(data, delimiter, pipe_fd[1]);
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
	int		fd2;

	fd2 = read_heredoc(data, *delimiter);
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	close(fd);
	if (fd < 0)
		return (-1);
	free(*delimiter);
	*delimiter = ft_strdup(HEREDOC_FILE);
	return (fd2);
}