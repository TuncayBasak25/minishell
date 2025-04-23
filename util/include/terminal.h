/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:01:00 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 08:33:08 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "core.h"

typedef struct termios	t_termios;

RESULT	term_get_original(t_termios **original);
RESULT	term_get_current(t_termios **current);

RESULT	term_enable_raw_mode(void);
RESULT	term_restore(void);

#endif