/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:38:20 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 10:31:51 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include <unistd.h>

RESULT	fd_read_to_buffer(t_fd fd, void *buffer, t_u32 buffer_size, t_u32 *byte_read)
{
	t_i32	read_result;

	read_result = read(fd, buffer, buffer_size);
	if (read_result == -1)
		return (fail(FNAME));
	*byte_read = read_result;
	return (SUCCESS);
}
