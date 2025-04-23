/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:10:16 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:26:26 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	string_init_static(t_string *self, char *buffer, t_u32 buffer_size)
{
	self->chars = buffer;
	self->len = 0;
	self->buffer.size = buffer_size;
}
