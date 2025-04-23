/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:10:16 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:32:57 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

RESULT	string_init_allocate(t_string *self, t_u32 cap)
{
	*self = (t_string){0};
	if (string_cap_extend(self, cap) == FAIL)
		return (fail("string_new_allocate: preallocation failed!"));
	return (SUCCESS);
}
