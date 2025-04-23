/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:40:16 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 09:44:46 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "string.h"

RESULT	string_cap_resize(t_string *self, t_u32 new_cap)
{
	if (buffer_resize(&self->buffer, new_cap) == FAIL)
		return (fail(FNAME));
	self->chars = self->buffer.ptr;
	if (self->len > new_cap)
		self->len = new_cap;
	return (SUCCESS);
}
