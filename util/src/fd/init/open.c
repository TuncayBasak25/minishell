/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:07:20 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 05:07:00 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include <fcntl.h>

RESULT	fd_open(t_fd *fd, const char *file_name, t_fdmode mode)
{
	*fd = open(file_name, mode);
	if (*fd == -1)
		return (FAIL);
	return (SUCCESS);
}
