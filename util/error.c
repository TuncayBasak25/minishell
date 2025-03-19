/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:27:52 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/18 11:47:03 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include <unistd.h>

void	print_error(const char *cstring)
{
	t_u32	len;

	len = 0;
	while (cstring[len])
		len++;
	write(2, cstring, len);
	write(2, "\n", 1);
}

t_result	fail(const char *cstring)
{
	print_error(cstring);
	return (FAIL);
}
