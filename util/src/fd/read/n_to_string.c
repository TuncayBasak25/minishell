/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_to_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:55:24 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 10:44:47 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include "string.h"
#include "math.h"

RESULT	fd_read_n_to_string(t_fd fd, t_string *string, t_u32 n)
{
	t_u32	read_count;

	if (string_cap_extend(string, n) == FAIL)
		return (fail(FNAME));
	if (fd_read_to_buffer(fd, string->chars + string->len, n, &read_count) == FAIL)
		return (fail(FNAME));
	string->len += read_count;
	return (SUCCESS);
}
