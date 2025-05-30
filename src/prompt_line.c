/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:34:59 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/30 15:01:55 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handle(int sigid)
{
	g_sig = sigid;
	close(0);
}

char	*prompt_line(const char *message)
{
	int		save_stdin;
	char	*line;

	if (isatty(0))
		printf("%s", message);
	save_stdin = dup(0);
	if (save_stdin == -1)
		return (NULL);
	g_sig = 0;
	signal(SIGINT, sigint_handle);
	if (isatty(0))
		line = readline("");
	else
		line = get_next_line(0);
	signal(SIGINT, SIG_IGN);
	if (g_sig == SIGINT)
	{
		dup2(save_stdin, 0);
		free(line);
		line = NULL;
	}
	close(save_stdin);
	return (line);
}
