/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_len.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 10:28:01 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:09:41 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUM_LEN_H
# define NUM_LEN_H

# define BASE_10 "0123456789"
# define BASE_16_LOWER "0123456789abcdef"
# define BASE_16_UPPER "0123456789ABCDEF"

# include "core.h"

t_u64	num_len_base_unsigned(t_u64 number, t_u64 base);
t_u64	num_len_base_signed(t_i64 number, t_u64 base);

#endif