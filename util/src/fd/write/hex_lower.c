/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_lower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:05:00 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 05:22:45 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include "string.h"

void	fd_write_hex_lower(t_fd fd, t_u64 number)
{
	t_string	string;
	char		buffer[16];

	string_init_static(&string, buffer, sizeof(buffer));
	string_push_hex_lower(&string, number);
	fd_write_string(fd, &string);
}
