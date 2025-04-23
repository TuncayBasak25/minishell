/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:05:00 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 05:17:14 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include "string.h"

void	fd_write_unsigned(t_fd fd, t_u64 number)
{
	t_string	string;
	char		buffer[16];

	string_init_static(&string, buffer, sizeof(buffer));
	string_push_unsigned(&string, number);
	fd_write_string(fd, &string);
}
