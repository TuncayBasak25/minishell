/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_raw_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:15:29 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 08:26:36 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "fd.h"
#include <termios.h>

RESULT	term_enable_raw_mode(void)
{
	t_termios	*current;

	if (term_get_current(&current) == FAIL)
		return (fail(FNAME));
    current->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(FD_STDIN, TCSAFLUSH, current) == -1)
		return (fail(FNAME));
	return (SUCCESS);
}
