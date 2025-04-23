/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 06:54:51 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:20:46 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

void	buffer_init_static(t_buffer *self, void *no_heap_ptr, t_u32 size)
{
	self->ptr = no_heap_ptr;
	self->size = size;
}
