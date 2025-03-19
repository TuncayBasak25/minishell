/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:36:41 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 15:15:09 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "sigaction.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>


volatile sig_atomic_t	g_sigid = 0;

void	signal_handler(int sigid)
{
	g_sigid = sigid;
	printf("SIgnal: %i\n", sigid);
}

int main()
{
	signal(SIGIO, signal_handler);
	while (TRUE)
	{
		pause();
		printf("\nCommande: %i...\n", g_sigid);
	}
}
