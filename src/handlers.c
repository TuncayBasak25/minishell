/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:06:37 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/23 22:33:53 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_prompt(int sigid)
{
	g_sig = sigid;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_exec(int sigid)
{
	g_sig = sigid;
}

void	quit_handler(int sigid)
{
	g_sig = sigid;
}

void	sigint_handler(int sigid)
{
	g_sig = sigid;
	rl_replace_line("", 0);
	close(0);
}
