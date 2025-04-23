/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:53:44 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 06:59:15 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "math.h"
#include "mem.h"
#include <stdlib.h>

RESULT	buffer_resize(t_buffer *self, t_u32 new_size)
{
	void	*new_ptr;

	if (new_size > 0)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (FAIL);
	}
	else
		new_ptr = NULL;
	mem_copy(new_ptr, self->ptr, umin(self->size, new_size));
	free(self->ptr);
	self->ptr = new_ptr;
	self->size = new_size;
	return (SUCCESS);
}
