/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:03:31 by tbasak            #+#    #+#             */
/*   Updated: 2025/03/19 07:31:32 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include "structs/s_string.h"

# define STRING_DEFAULT_MIN_CAP 16

void	string_init(t_string *self);
void	string_init_static(t_string *self, char *buffer, t_u32 buffer_size);
RESULT	string_init_allocate(t_string *self, t_u32 capacity);

RESULT	string_cap_resize(t_string *self, t_u32 new_cap);
RESULT	string_cap_extend(t_string *self, t_u32 char_count);

void	string_destroy(t_string *self);

void	string_push(t_string *self, const char *buffer, t_u32 buffer_size);
void	string_push_char(t_string *self, char c);
void	string_push_cstring(t_string *self, const char *cstring);
void	string_push_string(t_string *self, t_string *other);

void	string_push_hex_lower(t_string *self, t_u64 number);
void	string_push_hex_upper(t_string *self, t_u64 number);

void	string_push_signed(t_string *self, t_i64 number);
void	string_push_unsigned(t_string *self, t_u64 number);

#endif