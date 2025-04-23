/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 04:59:37 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/21 05:00:48 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_copy(void *dst, const void *src, t_u32 n)
{
	t_u8	*dst_byte;
	t_u8	*src_byte;

	if (n > 0 && (!dst || !src))
	{
		error_log("mem_copy: dst or src null when n > 0");
		return ;
	}
	dst_byte = (t_u8 *)dst;
	src_byte = (t_u8 *)src;
	while (n--)
		*dst_byte++ = *src_byte++;
}
