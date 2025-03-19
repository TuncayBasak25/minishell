/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sigaction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:44:36 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 14:40:37 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"

RESULT	setup_sigaction(t_i32 sigid, t_sa_handler handler)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (fail("Error sigemptyset"));
	if (sigaction(sigid, &sa, 0) == -1)
		return (fail("Error sigaction!"));
	return (SUCCESS);
}
