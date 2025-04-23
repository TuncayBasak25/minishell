/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:11 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:14:27 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "mem.h"

void	string_push(t_string *self, const char *buffer, t_u32 buffer_size)
{
	if (string_cap_extend(self, buffer_size) == FAIL)
		return ;
	mem_copy(self->chars + self->len, buffer, buffer_size);
	self->len += buffer_size;
}
