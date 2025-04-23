/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:16:47 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 05:10:00 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fd.h"

void	fd_write_buffer(t_fd fd, const void *buffer, t_u32 buffer_size)
{
	write(fd, buffer, buffer_size);
}
