/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_original.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:04:56 by tbasak            #+#    #+#             */
/*   Updated: 2025/05/07 13:25:03 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include <termios.h>

RESULT	term_get_original(t_termios **original)
{
	static t_termios	original_state = (t_termios){0};
	static t_bool		setled = FALSE;

	*original = &original_state;
	if (setled)
		return (SUCCESS);
	if (tcgetattr(1, &original_state) == -1)
		return (FAIL);
	setled = TRUE;
	return (SUCCESS);
}
