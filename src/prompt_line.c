/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:34:59 by tbasak            #+#    #+#             */
/*   Updated: 2025/06/03 16:39:04 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	signal_notify(int sigid)
{
	g_sig = sigid;
}

static void	sigint_close_stdin(int sigid)
{
	g_sig = sigid;
	close(0);
}

static void	setup_signals(t_shell *data)
{
	g_sig = 0;
	signal(SIGQUIT, signal_notify);
	signal(SIGINT, sigint_close_stdin);
	if (data->tester_pid)
		kill(data->tester_pid, SIGUSR1);
}

char	*prompt_line(t_shell *data, const char *message)
{
	int		save_stdin;
	char	*line;

	save_stdin = dup(0);
	if (save_stdin == -1)
		return (NULL);
	setup_signals(data);
	if (isatty(0))
		line = readline(message);
	else
	{
		line = get_next_line(0);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	if (g_sig == SIGINT)
	{
		dup2(save_stdin, 0);
		free(line);
		line = NULL;
	}
	close(save_stdin);
	signal(SIGINT, signal_notify);
	return (line);
}
