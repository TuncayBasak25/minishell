/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:21:38 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 06:42:51 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include "core.h"
# include "structs/s_buffer.h"

void	buffer_init(t_buffer *self);
void	buffer_init_static(t_buffer *self, void *no_heap_ptr, t_u32 size);
RESULT	buffer_init_allocate(t_buffer *self, t_u32 size);

void	buffer_copy(t_buffer *dst, t_buffer *src);
void	buffer_ncopy(t_buffer *dst, t_buffer *src, t_u32 n);

RESULT	buffer_resize(t_buffer *self, t_u32 new_size);

#endif