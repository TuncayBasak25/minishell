/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:34:22 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/18 23:22:49 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "cstring.h"

void	string_push_cstring(t_string *self, const char *cstring)
{
	string_push(self, cstring, cstring_len(cstring));
}
