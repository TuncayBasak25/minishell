/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:05:00 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 05:14:33 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include "cstring.h"

void	fd_write_cstring(t_fd fd, const char *cstring)
{
	fd_write_buffer(fd, cstring, cstring_len(cstring));
}
