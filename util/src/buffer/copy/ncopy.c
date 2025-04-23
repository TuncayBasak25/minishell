/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncopy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 06:57:12 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 06:58:35 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "math.h"
#include "mem.h"

void	buffer_ncopy(t_buffer *dst, t_buffer *src, t_u32 n)
{
	n = umin(n, dst->size);
	n = umin(n, src->size);
	mem_copy(dst->ptr, src->ptr, n);
}
