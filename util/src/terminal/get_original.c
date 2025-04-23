/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_original.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:04:56 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 09:04:51 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "fd.h"
#include <termios.h>

RESULT	term_get_original(t_termios **original)
{
	static t_termios	original_state = (t_termios){0};
	static t_bool		setled = FALSE;

	*original = &original_state;
	if (setled)
		return (SUCCESS);
	if (tcgetattr(FD_STDIN, &original_state) == -1)
		return (fail(FNAME));
	setled = TRUE;
	return (SUCCESS);
}
