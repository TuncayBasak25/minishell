/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:06:37 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/31 11:21:42 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_handler(int sigid)
{
	g_sig = sigid;
}

void	handle_sigquit_message(int status, pid_t pid, pid_t last_pid)
{
	if (WIFSIGNALED(status))
	{
		g_sig = WTERMSIG(status);
		if (g_sig == SIGQUIT && pid == last_pid)
			write(1, "Quit\n", 5);
		else if (g_sig == SIGQUIT)
			write(1, "^\\", 2);
	}
}
