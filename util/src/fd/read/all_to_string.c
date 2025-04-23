/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_to_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:55:24 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 10:14:50 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include "string.h"
#include "math.h"
#include <stdint.h>

RESULT	fd_read_all_to_string(t_fd fd, t_string *string)
{
	t_u64	file_size;

	if (fd_stat_byte_count(fd, &file_size) == FAIL)
		return (fail(FNAME));
	if (file_size > UINT32_MAX)
		return (fail("fd_read_all_to_string: file_size > u32_max"));
	if (fd_read_n_to_string(fd, string, file_size) == FAIL)
		return (fail(FNAME));
	return (SUCCESS);
}
