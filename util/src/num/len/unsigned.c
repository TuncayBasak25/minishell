/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:54:43 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 06:37:09 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num/num_len.h"

t_u64	num_len_base_unsigned(t_u64 number, t_u64 base)
{
	t_u8	len;

	if (base < 2)
		return (0);
	if (number == 0)
		return (1);
	len = 0;
	while (number > 0)
	{
		len++;
		number /= base;
	}
	return (len);
}
