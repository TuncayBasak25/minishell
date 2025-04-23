/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_buffer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:27:42 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:29:33 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_BUFFER_H
# define S_BUFFER_H

# include "core.h"

typedef struct s_buffer
{
	void	*ptr;
	t_u32	size;
}			t_buffer;

#endif