/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:27:01 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 08:28:56 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "fd.h"
#include <termios.h>

RESULT	term_restore(void)
{
	t_termios	*original;

	if (term_get_original(&original) == FAIL)
		return (fail(FNAME));
	if (tcsetattr(FD_STDIN, TCSAFLUSH, original) == -1)
		return (fail(FNAME));
	return (SUCCESS);
}
