/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:59:32 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:16:35 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "num/num_len.h"

static void	string_push_hex(t_string *self, t_u64 number, const char *base)
{
	t_u32	num_len;

	if (number == 0)
	{
		string_push_char(self, '0');
		return ;
	}
	num_len = num_len_base_unsigned(number, 16);
	if (string_cap_extend(self, num_len) == FAIL)
		return ;
	self->len += num_len;
	num_len = self->len;
	while (number > 0)
	{
		self->chars[--num_len] = base[number % 16];
		number /= 16;
	}
}

void	string_push_hex_lower(t_string *self, t_u64 number)
{
	string_push_hex(self, number, BASE_16_LOWER);
}

void	string_push_hex_upper(t_string *self, t_u64 number)
{
	string_push_hex(self, number, BASE_16_UPPER);
}
