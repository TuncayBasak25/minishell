/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:59:32 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:15:59 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "num/num_len.h"

void	string_push_unsigned(t_string *self, t_u64 number)
{
	t_u32	num_len;

	if (number == 0)
	{
		string_push_char(self, '0');
		return ;
	}
	num_len = num_len_base_unsigned(number, 10);
	if (string_cap_extend(self, num_len) == FAIL)
		return ;
	self->len += num_len;
	num_len = self->len;
	while (number > 0)
	{
		self->chars[--num_len] = '0' + number % 10;
		number /= 10;
	}
}
