/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:27:01 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/07 13:25:16 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include <termios.h>

RESULT	term_restore(void)
{
	t_termios	*original;

	if (term_get_original(&original) == FAIL)
		return (FAIL);
	if (tcsetattr(1, TCSAFLUSH, original) == -1)
		return (FAIL);
	return (SUCCESS);
}
