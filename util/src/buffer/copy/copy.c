/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 06:57:12 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 06:58:05 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "math.h"
#include "mem.h"

void	buffer_copy(t_buffer *dst, t_buffer *src)
{
	mem_copy(dst->ptr, src->ptr, umin(dst->size, src->size));
}
