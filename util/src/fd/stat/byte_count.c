/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:03:29 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 10:15:53 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include <sys/stat.h>
#include <sys/ioctl.h>

RESULT	fd_stat_byte_count(t_fd fd, t_u64 *byte_count)
{
    struct stat st;
	t_i32		available;

    if (fstat(fd, &st) == -1)
		return (fail("fd_stat_byte_count: fstat failed!"));
	if (S_ISREG(st.st_mode))
	{
		*byte_count = st.st_size;
		return (SUCCESS);
	}
	if (ioctl(fd, FIONREAD, &available) == -1)
        return (fail("fd_stat_byte_count: FIONREAD failed!"));
    *byte_count = available;
	return (SUCCESS);
}
