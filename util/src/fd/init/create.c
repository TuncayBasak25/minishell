/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:07:20 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 06:54:22 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include <fcntl.h>

RESULT	fd_create(t_fd *fd, const char *file_name, t_fdmode mode)
{
	if (mode == FD_READ)
	{
		error_log("fd_create: needs at least write permission!");
		return (FAIL);
	}
	*fd = open(file_name, mode | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
		return (FAIL);
	return (SUCCESS);
}
