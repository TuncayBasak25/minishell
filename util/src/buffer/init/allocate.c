/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 06:54:51 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:23:52 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

RESULT	buffer_init_allocate(t_buffer *self, t_u32 size)
{
	*self = (t_buffer){0};
	return (buffer_resize(self, size));
}
