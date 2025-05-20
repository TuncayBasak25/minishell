/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:06:37 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/20 20:02:09 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_prompt(int sigid)
{
	(void)sigid;
	write(1, "\n", 1);  // Print newline
	rl_on_new_line();               // Move to new prompt line
	rl_replace_line("", 0);        // Clear the current input
	rl_redisplay();
}

void	sigint_exec(int sigid)
{
	g_sig = sigid;
}

void	quit_handler(int sigid)
{
	g_sig = sigid;
	write(1, "Quit", 4);
}
