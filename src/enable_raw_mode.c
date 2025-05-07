/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_raw_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:15:29 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/07 13:24:32 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include <termios.h>

RESULT	term_enable_raw_mode(void)
{
	t_termios	*current;

	if (term_get_current(&current) == FAIL)
		return (FAIL);
    current->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(1, TCSAFLUSH, current) == -1)
		return (FAIL);
	return (SUCCESS);
}
